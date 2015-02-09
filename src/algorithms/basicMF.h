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
	virtual int predict() const;
	virtual void load(const char* inputFile);
	virtual void save(const char* outputFile) const;
private:
	double calculate(int u_id,int i_id) const;
	int num_fact;
	int num_user;
	int num_item;
	double** Item_feature;
	double** User_feature;
	//double *sigma;
	double *bias_u,*bias_i;
};

#endif