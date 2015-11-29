#ifndef RSPACKAGE_ALGORITHMS_BASICSOLVER_H_
#define RSPACKAGE_ALGORITHMS_BASICSOLVER_H_

#include "../data/rating.h"
#include <cstddef>
class basicSolver
{
public:
	basicSolver(const char* inputFile,const int mode=0);
	virtual ~basicSolver();
	virtual int train(const char* inputFile=NULL)=0;
	virtual double predict(const char* inputFile) const=0;
	virtual void load(const char* inputFile)=0;
	virtual void save(const char* outputFile) const =0;
	virtual void Init()=0;
protected:
	rating* data;
};

#endif