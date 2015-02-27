#ifndef RSPACKAGE_ALGORITHMS_BASICMF_H_
#define RSPACKAGE_ALGORITHMS_BASICMF_H_

#include "basicSolver.h"

class basicMF:public basicSolver
{
public:
	basicMF(const char* inputFile,int n=12);
	virtual ~basicMF();
	virtual void Init();
	virtual int train();
	virtual double predict(const char* inputFile) const;
	virtual void load(const char* inputFile);
	virtual void save(const char* outputFile) const;
private:
	inline double calculate(int u_id,int i_id) const;
	inline void update(double err,int u_id,int i_id);
	int num_fact;
	int num_user;
	int num_item;
	double** Item_feature;
	double** User_feature;
	//double *sigma;
	double *bias_u,*bias_i;
};

#endif