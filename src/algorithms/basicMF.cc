#include "basicMF.h"
//#include "basicSolver.cc"
//#include "basicSolver.h"

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include <random>
#include <algorithm>
#include <omp.h>



const double EPSIRON=0.05;
const int MAXN=20;
const double lamda=0.005;
const double learning_rate=0.005;

basicMF::basicMF(const char* inputFile,const int num_feat,const int batch_size):num_fact(num_feat),batch_size(batch_size),basicSolver(inputFile,0){
	std::cout<<data->getUsercount()<<data->getItemcount()<<std::endl;
}

basicMF::~basicMF(){
	for(int i=0;i<num_item;i++)
		delete []Item_feature[i];
	for(int i=0;i<num_user;i++)
		delete []User_feature[i]; 
	delete []Item_feature;
	delete []User_feature;
	delete []bias_u;
	delete []bias_i;
}

void basicMF::load(const char* inputFile){
	int flag;
	delete data;
	data=new rating();
	flag=data->Init(inputFile);
	switch(flag){
		case -1:std::cout<<"File not exist!"<<std::endl;break;
		case -2:break;
		default:break;
	}
}

void basicMF::Init(){
	num_item=data->getItemcount();
	num_user=data->getUsercount();
	Item_feature=new double*[num_item];
	User_feature=new double*[num_user];
	bias_u=new double[num_user];
	bias_i=new double[num_item];
	memset(bias_u,0,sizeof(double)*num_user);
	memset(bias_i,0,sizeof(double)*num_item);
	for(int i=0;i<num_user;i++)
		User_feature[i]=new double[num_fact];
	for(int i=0;i<num_item;i++)
		Item_feature[i]=new double[num_fact];
	std::random_device rd;
    std::mt19937 gen(rd());
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d(0,EPSIRON);
	for (int i=0;i<num_item;i++)
		for (int j=0;j<num_fact;j++)
			//change it into Gaussian distribution
			Item_feature[i][j]=std::round(d(gen));
	for (int i=0;i<num_user;i++)
		for (int j=0;j<num_fact;j++)
			User_feature[i][j]=std::round(d(gen));
}

double basicMF::calculate(int u_id,int i_id) const{
	double pre=0;
	int j;
	pre=3+bias_u[u_id]+bias_i[i_id];//+sigma[item]*delta/(delta+rating_date-item_begin[item]);
	for (j=0;j<num_fact;j++)
			pre+=Item_feature[i_id][j]*User_feature[u_id][j]; //transpose will get better local performance
	if (pre>5) pre=5;
	if (pre<1) pre=1;
	return pre;
}

int basicMF::train(const char* inputFile){
	int epoch=0;
	//int i,j;
	double pre;
	double *err;
	int *user,*item;
	user=new int[batch_size];
	item=new int[batch_size];
	err=new double[batch_size];
	int count=data->getRatingcount();
	int limited;
	std::vector<record> *mat=data->getTrainpair();
	double err_1=999,err_2=1000;
	auto engine = std::default_random_engine{};
	std::cout<<omp_get_num_procs()<<std::endl;
	while(epoch<MAXN&&fabs(err_1-err_2)>0.00001){
		err_2=err_1;
		err_1=0;
		std::shuffle(mat->begin(), mat->end(), engine);
		for (int i=0;i<mat->size();i+=batch_size){
			if (i+batch_size>=mat->size())
				limited=mat->size()-i-1;
			else
				limited=batch_size;
			
			//#pragma omp parallel for
			for(int j=0;j<limited;++j){
				user[j]=mat->at(i+j).user_id-1;
				item[j]=mat->at(i+j).item_id-1;
				pre=calculate(user[j],item[j]);
				err[j]=mat->at(i+j).rating-pre;
			}
			for(int j=0;j<limited;++j){
				err_1+=pow(err[j],2);
			}
			update(err,user,item);
			
		}
		if (inputFile)
			err_1=predict(inputFile);
		else
			err_1=sqrt(err_1/count);	
		std::cout<<"Epoch:"<<epoch<<" the error is "<<err_1<<std::endl;
		epoch++;
	}
	delete user;
	delete item;
	delete err;
	return epoch;
}

void basicMF::update(double err[],int u_id[],int i_id[]){
	//#pragma omp parallel for
	for (int k = 0; k < batch_size; ++k){
		//#pragma omp parallel for
		for(int i=0;i<num_fact;i++){
			Item_feature[i_id[k]][i]+=learning_rate*(err[k]*User_feature[u_id[k]][i]-lamda*Item_feature[i_id[k]][i]);
			User_feature[u_id[k]][i]+=learning_rate*(err[k]*Item_feature[i_id[k]][i]-lamda*User_feature[u_id[k]][i]);
		}
		bias_u[u_id[k]]+=learning_rate*(err[k]-lamda*bias_u[u_id[k]]);
		bias_i[i_id[k]]+=learning_rate*(err[k]-lamda*bias_i[i_id[k]]);
	}
}

double basicMF::predict(const char* inputFile) const{
	std::ifstream fin;
	int u_id,i_id,t;
	double r;
	double err=0;
	int count;
	fin.open(inputFile,std::ios::in);
	if (!fin.is_open())
		return -1;
	count=0;
	while(!fin.eof()){
		fin>>u_id>>i_id>>r>>t;
		err+=pow(r-calculate(u_id-1,i_id-1),2);
		++count;
	}
	err/=count;
	fin.close();
	return sqrt(err);
}

void basicMF::save(const char* outputFile) const{

}
