#include "basicMF.h"
#include "basicSolver.cc"

#include <cstdlib>
#include <iostream>

const double EPSIRON=0.1;
const int MAXN=100;
const double lamda=0.01;
const double learning_rate=0.0001;
basicMF::basicMF(const char* inputFile,int n):num_fact(n),basicSolver(inputFile){
	std::cout<<data->getUsercount()<<data->getItemcount()<<std::endl;
}

basicMF::~basicMF(){

}

void basicMF::load(const char* inputFile){
	int flag;
	data=new rating();
	flag=data->Init(inputFile);
	switch(flag){
		case -1:std::cout<<"File not exist!"<<std::endl;break;
		case -2:break;
		default:break;
	}
}

void basicMF::Init(){
	Item_feature=new double*[num_fact];
	User_feature=new double*[num_fact];
	num_item=data->getItemcount();
	num_user=data->getUsercount();
	bias_u=new double[num_user];
	bias_i=new double[num_item];
	memset(bias_u,0,sizeof(double)*num_user);
	memset(bias_i,0,sizeof(double)*num_item);
	for(int i=0;i<num_fact;i++){
		User_feature[i]=new double[num_fact];
		Item_feature[i]=new double[num_user];
	}
	for (int i=0;i<num_fact;i++)
		for (int j=0;j<num_item;j++)
			Item_feature[i][j]=rand()%100/100.0*(2*EPSIRON)-EPSIRON;
	for (int i=0;i<num_fact;i++)
		for (int j=0;j<num_user;j++)
			User_feature[i][j]=rand()%100/100.0*(2*EPSIRON)-EPSIRON;
}

double basicMF::calculate(int u_id,int i_id) const{
	double pre=0;
	int j;
	pre=3+bias_u[u_id]+bias_i[i_id];//+sigma[item]*delta/(delta+rating_date-item_begin[item]);
	/*if (isnan(pre)){
		cout<<bias_u[user]<<' '<<bias_i[item]<<endl;
		cout<<sigma[item]*delta/(delta+rating_date-item_begin[item])<<endl;
		cout<<user<<item<<endl;
		exit(0);
	}*/
	for (j=0;j<num_fact;j++)
		//if (Item_feature[j][item]!=0&&User_feature[j][user]!=0)
			pre+=Item_feature[j][u_id]*User_feature[j][i_id];
	if (pre>5) pre=5;
	if (pre<1) pre=1;
	return pre;
}

int basicMF::train(){
	int epoch=0;
	int i,j;
	int count=0;
	int maxi=data->getUsercount();
	int maxj=data->getItemcount();
	double err_1=0,err_2=1;
	while(epoch<MAXN&&err_1<err_2){
		for(i=0;i<maxi;i++)
			for(j=0;j<maxj;j++)
				if (data->getRating(i+1,j+1))
					count++;
		std::cout<<count<<std::endl;
		break;
	}
	return 0;
}

int basicMF::predict() const{
	return 0;
}

void basicMF::save(const char* outputFile) const{

}