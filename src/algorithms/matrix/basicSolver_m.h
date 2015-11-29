#ifndef RSPACKAGE_ALGORITHMS_MATRIX_BASICSOLVER_H_//
#define RSPACKAGE_ALGORITHMS_MATRIX_BASICSOLVER_H_

#include "../../data/matrix/rating_m.h"
#include <cstddef>

class basicSolver_m
{
public:
	basicSolver_m(const char* inputFile);
	virtual ~basicSolver_m();
	virtual int train(const char* inputFile=NULL)=0;
	virtual double predict(const char* inputFile) const=0;
	virtual void load(const char* inputFile)=0;
	virtual void save(const char* outputFile) const =0;
	virtual void Init()=0;
protected:
	rating_m* data;
};

#endif