#include "basicMF_m.h"
//#include "basicSolver_m.cc"
//#include "basicSolver.h"

#include "../../Eigen/Core"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include <random>
#include <algorithm>
#include <omp.h>

/*const double EPSIRON=0.1;
const int MAXN=20;
const double lamda=0.005;
const double learning_rate=0.003;*/
const double EPSIRON=0.05;
const int MAXN=20;
const double lamda=0.005;
const double learning_rate=0.005;



basicMF_m::basicMF_m(const char* inputFile,const int n,const int batch_size):num_fact(n),batch_size(batch_size),basicSolver_m(inputFile){
	std::cout<<data->getUsercount()<<data->getItemcount()<<std::endl;
}

basicMF_m::~basicMF_m(){
	/*for(int i=0;i<num_item;i++)
		delete []Item_feature[i];
	for(int i=0;i<num_user;i++)
		delete []User_feature[i]; 
	delete []Item_feature;
	delete []User_feature;
	delete []bias_u;
	delete []bias_i;*/
}

void basicMF_m::load(const char* inputFile){
	int flag;
	delete data;
	data=new rating_m();
	flag=data->Init(inputFile);
	switch(flag){
		case -1:std::cout<<"File not exist!"<<std::endl;break;
		case -2:break;
		default:break;
	}
}

void basicMF_m::Init(){
	num_item=data->getItemcount();
	num_user=data->getUsercount();
	//Item_feature=new double*[num_item];
	//User_feature=new double*[num_user];
	Item_feature.resize(num_item,num_fact);
	User_feature.resize(num_user,num_fact);
	//bias_u=new double[num_user];
	//bias_i=new double[num_item];
	bias_u.resize(num_user);
	bias_i.resize(num_item);
	bias_u.setZero();
	bias_i.setZero();
	std::random_device rd;
    std::mt19937 gen(rd());
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d(0,EPSIRON);
	for (int i=0;i<num_item;i++)
		for (int j=0;j<num_fact;j++)
			//Item_feature.row(i)=nrandn(num_fact);
			Item_feature(i,j)=std::round(d(gen));
	for (int i=0;i<num_user;i++)
		for (int j=0;j<num_fact;j++)
			User_feature(i,j)=std::round(d(gen));
}

double basicMF_m::calculate(int u_id,int i_id) const{
	double pre=0;
	//int j;
	//pre=3;
	pre=3+bias_u(u_id)+bias_i(i_id);//+sigma[item]*delta/(delta+rating_date-item_begin[item]);
	/*if (isnan(pre)){
		cout<<bias_u[user]<<' '<<bias_i[item]<<endl;
		cout<<sigma[item]*delta/(delta+rating_date-item_begin[item])<<endl;
		cout<<user<<item<<endl;
		exit(0);
	}*/
	//for (j=0;j<num_fact;j++)
		//if (Item_feature[j][item]!=0&&User_feature[j][user]!=0)
			pre+=Item_feature.row(i_id)*User_feature.row(u_id).transpose(); //transpose will get better local performance
	if (pre>5) pre=5;
	if (pre<1) pre=1;
	return pre;
}

int basicMF_m::train(const char* inputFile){
	int epoch=0;
	double pre;
	double *err;
	int *user,*item;
	user=new int[batch_size];
	item=new int[batch_size];
	err=new double[batch_size];
	//int maxi=data->getUsercount();
	//int maxj=data->getItemcount();
	int count=data->getRatingcount();
	int limited;
	std::vector<record> *mat=data->getTrainpair();
	double err_1=999,err_2=1000;
	std::random_device rd;
    std::mt19937 g(rd());
 	std::cout<<omp_get_num_procs()<<std::endl;
	while(epoch<MAXN&&fabs(err_1-err_2)>0.00001){
		err_2=err_1;
		err_1=0;
		//std::cout<<"batch_size"<<batch_size<<std::endl;
		std::shuffle(mat->begin(), mat->end(), g);
		//std::cout<<"1"<<std::endl;
		//std::cout<<mat->at(0).user_id<<std::endl;
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
		/*for (int k=0; k<mat->outerSize(); ++k)
			for (Eigen::SparseMatrix<int>::InnerIterator it(*mat,k); it; ++it){
				i=it.row();
				j=it.col();
				if ((ori=data->getRating(i+1,j+1))){
					pre=calculate(i,j);
					err=ori-pre;
					//std::cout<<"here"<<i<<j<<std::endl;
					update(err,i,j);
					err_1+=pow(err,2);
				}
			}*/
		/*for(i=0;i<maxi;i++)
			for(j=0;j<maxj;j++)
				if ((ori=data->getRating(i+1,j+1))){
					pre=calculate(i,j);
					err=ori-pre;
					std::cout<<"here"<<i<<j<<std::endl;
					update(err,i,j);
					err_1+=pow(err,2);
				}*/
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

void basicMF_m::update(double err[],int u_id[],int i_id[]){
	/*for(int i=0;i<num_fact;i++){
		Item_feature[i_id][i]+=learning_rate*(err*User_feature[u_id][i]-lamda*Item_feature[i_id][i]);
		User_feature[u_id][i]+=learning_rate*(err*Item_feature[i_id][i]-lamda*User_feature[u_id][i]);
		bias_u[u_id]+=learning_rate*(err-lamda*bias_u[u_id]);
		bias_i[i_id]+=learning_rate*(err-lamda*bias_i[i_id]);
	}*/
	//#pragma omp parallel for
	for (int i = 0; i < batch_size; ++i)
	{
		Item_feature.row(i_id[i])+=learning_rate*(err[i]*User_feature.row(u_id[i])-lamda*Item_feature.row(i_id[i]));
		User_feature.row(u_id[i])+=learning_rate*(err[i]*Item_feature.row(i_id[i])-lamda*User_feature.row(u_id[i]));
		bias_u(u_id[i])+=learning_rate*(err[i]-lamda*bias_u(u_id[i]));
		bias_i(i_id[i])+=learning_rate*(err[i]-lamda*bias_i(i_id[i]));
	}
	
}
double basicMF_m::predict(const char* inputFile) const{
	std::ifstream fin;
	int u_id,i_id,r,t;
	double err=0;
	int count;
	fin.open(inputFile,std::ios::in);
	if (!fin.is_open())
		return -1;
	count=0;
	while(!fin.eof()){
		fin>>u_id>>i_id>>r>>t;
		err+=pow(r-calculate(u_id-1,i_id-1),2);
		//err+=fabs(r-calculate(u_id-1,i_id-1));
		count++;
	}
	err/=count;
	//std::cout<<"Count:"<<count<<std::endl;
	//std::cout<<"Predict error:"<<sqrt(err)<<std::endl;
	return sqrt(err);
}

void basicMF_m::save(const char* outputFile) const{

}