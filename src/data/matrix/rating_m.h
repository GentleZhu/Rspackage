#ifndef RSPACKAGE_DATA_MATRIX_RATING_H_
#define RSPACKAGE_DATA_MATRIX_RATING_H_

#include "../../Eigen/Dense"
#include <set>
class rating_m{
public:
	explicit rating_m();
	int Init(const char* filepath);
	int getRating(const int u_id,const int i_id) const;
	int getTime(const int u_id,const int i_id) const;
	int getUsercount() const;
	int getItemcount() const;
	int getRatingcount() const;
	~rating_m();
private:
	int user_count;
	int item_count;
	int rating_count;
	int max_item;
	int ratings_count;
	std::set<int> user_id;
	std::set<int> item_id;
	Eigen::MatrixXi ratings;
	Eigen::MatrixXi timestamp;
};
#endif