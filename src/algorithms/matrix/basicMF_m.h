#ifndef RSPACKAGE_ALGORITHMS_MATRIX_BASICMF_H_
#define RSPACKAGE_ALGORITHMS_MATRIX_BASICMF_H_

#include "basicSolver_m.h"
#include <cstddef>

class basicMF_m:public basicSolver_m
{
public:
	basicMF_m(const char* inputFile,const int n=12,const int batch_size=1);
	virtual ~basicMF_m();
	virtual void Init();
	virtual int train(const char* inputFile=NULL);
	virtual double predict(const char* inputFile) const;
	virtual void load(const char* inputFile);
	virtual void save(const char* outputFile) const;
private:
	inline double calculate(int u_id,int i_id) const;
	inline void update(double err[],int u_id[],int i_id[]);
	int num_fact;
	int num_user;
	int num_item;
	int batch_size;
	Eigen::MatrixXd Item_feature;
	Eigen::MatrixXd User_feature;
	Eigen::VectorXd bias_u,bias_i;
};

#endif