#ifndef RSPACKAGE_ALGORITHMS_BASICSOLVER_H_
#define RSPACKAGE_ALGORITHMS_BASICSOLVER_H_

#include "../data/rating.cc"
class basicSolver
{
public:
	basicSolver(const char* inputFile);
	virtual ~basicSolver();
	virtual int train()=0;
	virtual int predict(const char* inputFile) const=0;
	virtual void load(const char* inputFile)=0;
	virtual void save(const char* outputFile) const =0;
	virtual void Init()=0;
protected:
	rating* data;
};

#endif