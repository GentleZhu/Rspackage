#ifndef RSPACKAGE_ALGORITHMS_BASICKNN_H_
#define RSPACKAGE_ALGORITHMS_BASICKNN_H_

#include <vector>

#include "basicSolver.h"

class basicKNN:public basicSolver
{	
public:
	basicKNN(const char* inputFile,int t=0);
	virtual ~basicKNN();
	virtual void Init();
	virtual int train(const char* inputFile=NULL);
	virtual double predict(const char* inputFile) const;
	virtual void load(const char* inputFile);
	virtual void save(const char* outputFile) const;
private:
	inline double calculate(int u_id,int i_id) const;
	inline void intersectionD(int i,int j,std::vector<int>& Dij);
	void Heap_Sort(int index,double cij) const;
	int num_user;
	int num_item;
	int type;
	double **W;
	double *mean;
	double *RSE;
	int *K_neighbor;
	std::vector<int> *D;
};

#endif