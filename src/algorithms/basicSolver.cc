#include "basicSolver.h"

basicSolver::basicSolver(const char* inputFile,const int mode){
	data=new rating(mode);
	data->Init(inputFile);
}

basicSolver::~basicSolver(){
	delete data;
}
