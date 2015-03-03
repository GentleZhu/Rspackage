#include "rating_m.h"

#include <cstdlib>
#include <fstream>

rating_m::rating_m(){
	user_count=0;
	item_count=0;
	ratings_count=0;
}

int rating_m::Init(const char* filepath){
	std::ifstream fin;
	int u_id,i_id,rt,tm;
	//auto tmp;
	int count=0;
	max_item=0;
	fin.open(filepath,std::ios::in);
	if (!fin.is_open())
		return -1;
	while(!fin.eof()){
		fin>>u_id>>i_id>>rt>>tm;
		max_item=i_id>max_item?i_id:max_item;
		//tmp=user_id.find(u_id);
		//if (tmp==user_id.end())
		if (user_id.count(u_id)==0)
			user_id.insert(u_id);
		//tmp=item_id.find(i_id);
		//if (tmp=item_id.end())
		if (item_id.count(i_id)==0)
			item_id.insert(i_id);
		++count;
	}
	rating_count=count;
	user_count=user_id.size();
	item_count=item_id.size();
	ratings.resize(user_count,max_item);
	timestamp.resize(user_count,max_item);
	//ratings=new int*[user_count];
	//timestamp=new int*[user_count];
	/*for(int i=0;i<user_count;i++){
		ratings[i]=new int[max_item];
		timestamp[i]=new int[max_item];
		memset(ratings[i],0,sizeof(int)*max_item);
		memset(timestamp[i],0,sizeof(int)*max_item);
	}*/
	//memset(ratings,0,sizeof(int)*user_count*item_count);
	//memset(timestamp,0,sizeof(int)*user_count*item_count);
	fin.clear();
	fin.seekg(0,std::ios::beg);
	//std::cout<<count<<std::endl;
	while(!fin.eof()){
		fin>>u_id>>i_id>>rt>>tm;
		ratings(u_id-1,i_id-1)=rt;
		timestamp(u_id-1,i_id-1)=tm;
		--count;
	}
    fin.close();
	if (count)
		return -2;
	else
		return 0;
}

int rating_m::getRating(const int u_id,const int i_id) const{
	if (!(u_id<=user_count&&i_id<=max_item))
		return -1;
	else
		return ratings(u_id-1,i_id-1);
}

int rating_m::getTime(const int u_id,const int i_id) const{
	if (!(u_id<=user_count&&i_id<=max_item))
		return -1;
	else
		return timestamp(u_id-1,i_id-1);
}

int rating_m::getUsercount() const{
	return user_count;
}

int rating_m::getItemcount() const{
	return max_item;
}

int rating_m::getRatingcount() const{
	return rating_count;
}

rating_m::~rating_m(){
	//std::cout<<"should be last"<<std::endl;
	user_id.clear();
	item_id.clear();
}