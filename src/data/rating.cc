#include "rating.h"

#include <cstdlib>
#include <fstream>
#include <cstring>
#include <iostream>

rating::rating(int mode){
	user_count=0;
	item_count=0;
	ratings_count=0;
	this->mode=mode;
	train_vec=new std::vector<record>();
}

int rating::Init(const char* filepath){
	std::ifstream fin;
	int u_id,i_id,tm;
	double rt;
	//auto tmp;
	int count=0;
	max_item=0;
	int max_user=0;
	fin.open(filepath,std::ios::in);
	if (!fin.is_open())
		return -1;
	while(!fin.eof()){
		fin>>u_id>>i_id>>rt>>tm;
		max_item=i_id>max_item?i_id:max_item;
		max_user=u_id>max_user?u_id:max_user;
		train_vec->emplace_back(u_id,i_id,rt,tm);
		//tmp=user_id.find(u_id);
		//if (tmp==user_id.end())
		if (user_id.count(u_id)==0)
			user_id.insert(u_id);
		//tmp=item_id.find(i_id);
		//if (tmp=item_id.end())
		if (item_id.count(i_id)==0)
			item_id.insert(i_id);
		++count;
		if (count%1000000==0)
			std::cout<<count<<std::endl;
	}
	rating_count=count;
	user_count=max_user;user_id.size();
	item_count=item_id.size();
	if (mode){
		ratings=new int*[user_count];
		timestamp=new int*[user_count];
		for(int i=0;i<user_count;i++){
			ratings[i]=new int[max_item];
			timestamp[i]=new int[max_item];
			std::memset(ratings[i],0,sizeof(int)*max_item);
			std::memset(timestamp[i],0,sizeof(int)*max_item);
		}
		//memset(ratings,0,sizeof(int)*user_count*item_count);
		//memset(timestamp,0,sizeof(int)*user_count*item_count);
		fin.clear();
		fin.seekg(0,std::ios::beg);
		//std::cout<<count<<std::endl;
		while(!fin.eof()){
			fin>>u_id>>i_id>>rt>>tm;
			ratings[u_id-1][i_id-1]=rt;
			timestamp[u_id-1][i_id-1]=tm;
			--count;
		}
	}
	if (count)
			return -2;
		else
			return 0;
	fin.close();
}

int rating::getRating(const int u_id,const int i_id) const{
	if (!(u_id<=user_count&&i_id<=max_item))
		return -1;
	else
		return ratings[u_id-1][i_id-1];
}

int rating::getTime(const int u_id,const int i_id) const{
	if (!(u_id<=user_count&&i_id<=max_item))
		return -1;
	else
		return timestamp[u_id-1][i_id-1];
}

std::vector<record> * rating::getTrainpair(){
	return train_vec;
};

int rating::getUsercount() const{
	return user_count;
}

int rating::getItemcount() const{
	return max_item;
}

int rating::getRatingcount() const{
	return rating_count;
}

rating::~rating(){
	//std::cout<<"should be last"<<std::endl;
	user_id.clear();
	item_id.clear();
	train_vec->clear();
	train_vec->shrink_to_fit();
	/*for(int i=0;i<user_count;i++){
		delete []ratings[i];
		delete []timestamp[i];
	}
	delete [] ratings;
	delete [] timestamp;*/
}