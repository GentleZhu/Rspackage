#ifndef RSPACKAGE_DATA_HEADER_H_
#define RSPACKAGE_DATA_HEADER_H_

struct record
{
	int user_id,item_id,timestamp;
	double rating;
	record(int uid,int iid,double rt,int tm):user_id(uid),item_id(iid),rating(rt),timestamp(tm){};
};

#endif