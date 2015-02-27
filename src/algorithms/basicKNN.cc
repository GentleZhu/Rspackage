#include "basicKNN.h"
#include "basicSolver.cc"

#include <cmath>

const int k=10;
basicKNN::basicKNN(const char* inputFile,int t):type(t),basicSolver(inputFile){
	std::cout<<data->getUsercount()<<data->getItemcount()<<std::endl;
}

basicKNN::~basicKNN(){
	delete []D;
	delete []mean;
	delete []RSE;
	for(int i=0;i<num_item;i++)
		delete []W[i];
	delete []W;
}

void basicKNN::Init(){
	num_item=data->getItemcount();
	num_user=data->getUsercount();
	W=new double*[num_item];
	D=new std::vector<int>[num_item];
	mean=new double[num_item];
	RSE=new double[num_item];
	K_neighbor=new int[k+1];
	memset(K_neighbor,0,sizeof(int)*(k+1));
	for (int i=0;i<num_item;i++)
		W[i]=new double[num_item];
	for (int i=0;i<num_user;i++)
		for(int j=0;j<num_item;j++)
			if (data->getRating(i+1,j+1))
				D[j].push_back(i);
}

int basicKNN::train(){
	double sum=0;
	for(int i=0;i<num_item;++i){
		sum=0;
		for(int j=0;j<num_user;++j)
			sum+=data->getRating(j+1,i+1);
		if (D[i].size())
			mean[i]=sum/D[i].size();
		else 
			mean[i]=0;
		sum=0;
		for (int j=0;j<D[i].size();++j)
			sum+=pow(data->getRating(D[i][j]+1,i+1)-mean[i],2);
		RSE[i]=sqrt(sum);
		//std::cout<<mean[i]<<std::endl;
	}
	std::vector<int> Dij;
	for(int i=0;i<num_item;i++){
		//std::cout<<i<<" "<<std::endl;
		for(int j=0;j<i;j++){
			double sum=0;
			intersectionD(i,j,Dij);
			for (std::vector<int>::iterator u=Dij.begin();u!=Dij.end();++u)
				if (!(data->getRating(*u+1,i+1)&&data->getRating(*u+1,j+1))){
					std::cout<<"Alert wrong!"<<std::endl;
				}
				else{
					//std::cout<<i<<" "<<j<<" "<<*u<<std::endl;
					sum+=(data->getRating(*u+1,i+1)-mean[i])*(data->getRating(*u+1,j+1)-mean[j]);
				}
			W[i][j]=W[j][i]=sum/(RSE[i]*RSE[j]);
			Dij.clear();
		}
	}
	//std::cout<<"W ok"<<std::endl;
	return 0;
}

double basicKNN::predict(const char* inputFile) const{
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
		memset(K_neighbor,0,sizeof(int)*(k+1));
		//err+=pow(r-calculate(u_id-1,i_id-1),2);
		err+=fabs(r-calculate(u_id-1,i_id-1));
		std::cout<<err<<'\t';
		/*if (isnan(err)){
			std::cout<<u_id<<" "<<i_id<<std::endl;
			std::cout<<calculate(u_id-1,i_id-1)<<std::endl;
			return 0;
		}*/
		count++;
	}
	err/=count;
	//std::cout<<"Count:"<<count<<std::endl;
	//std::cout<<"Predict error:"<<sqrt(err)<<std::endl;
	fin.close();
	return sqrt(err);
	//return err;
}

void basicKNN::load(const char* inputFile){
	data=new rating();
	int flag=data->Init(inputFile);
	switch(flag){
		case -1:std::cout<<"File not exist!"<<std::endl;break;
		case -2:break;
		default:break;
	}
}

void basicKNN::save(const char* inputFile) const{

}

double basicKNN::calculate(int u_id,int i_id) const{
	double sumR=0,sumW=0;
	if (data->getRating(u_id+1,i_id+1)){
		std::cout<<"exist!"<<std::endl;
		return data->getRating(u_id+1,i_id+1);
	}
	for(int i=0;i<num_item;i++)
		if (data->getRating(u_id+1,i+1)&&i!=i_id){
			/*if (W[i_id][i]>0.15){
				sumR+=W[i_id][i]*(double)data->getRating(u_id+1,i+1);
				sumW+=W[i_id][i];
			}*/
			Heap_Sort(i,W[i_id][i]);
		}
	for(int i=1;i<=k;i++)
		if (K_neighbor[i]%10000>0){
			int index=K_neighbor[i]%10000-1;
			sumR+=W[i_id][index]*(double)data->getRating(u_id+1,index+1);
			sumW+=W[i_id][index];
		}
	if (sumW>0){
		if (sumR/sumW>5)
			return 5;
		else if (sumR/sumW<1)
			return 1;
		else 
			return sumR/sumW;
	}
	else
		return 3;//Cold start problem
}

void basicKNN::intersectionD(int i,int j,std::vector<int>& Dij){
	int p,q;
	for(p=0,q=0;p<D[i].size()&&q<D[j].size();){
		if (D[i][p]<D[j][q])
			++p;
		else if (D[i][p]>D[j][q])
			++q;
		else{
			Dij.push_back(D[i][p]);
			++p;
			++q;
		}
	}
	/*for(int i=0;i<Dij.size();i++)
		std::cout<<Dij[i]<<" "<<std::endl;*/
	//std::cout<<"ok"<<std::endl;
}

void basicKNN::Heap_Sort(int index,double cij) const{
	int Cij_index;
	int i;
	int size=k;
	int p,child;
	Cij_index=(int)(cij*100)*10000+index+1;
	if (Cij_index>K_neighbor[1]){
		//Heap[1]=data;
		p=Cij_index;
		for(i=1;i*2<=size;i=child){
     		child=2*i;
     		if (child!=size&&K_neighbor[child]>K_neighbor[child+1]) 
     			child++;
     		if (K_neighbor[child]<p) 
     			K_neighbor[i]=K_neighbor[child];
     		else break;
     	}
     	K_neighbor[i]=p;
	}
}