#ifndef RSPACKAGE_DATA_RATING_H_
#define RSPACKAGE_DATA_RATING_H_

#include "header.h"

#include <set>
#include <vector>

class rating{
public:
	explicit rating(const int mode=0);
	int Init(const char* filepath);
	int getRating(const int u_id,const int i_id) const;
	int getTime(const int u_id,const int i_id) const;
	std::vector<record> * getTrainpair();
	int getUsercount() const;
	int getItemcount() const;
	int getRatingcount() const;
	~rating();
private:
	int user_count;
	int item_count;
	int rating_count;
	int max_item;
	int ratings_count;
	int mode;
	std::set<int> user_id;
	std::set<int> item_id;
	std::vector<record> *train_vec;
	int** ratings;
	int** timestamp;
};
#endif