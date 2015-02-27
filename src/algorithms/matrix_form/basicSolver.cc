#include "basicSolver.h"

basicSolver::basicSolver(const char* inputFile){
	data=new rating();
	data->Init(inputFile);
}

basicSolver::~basicSolver(){
	delete data;
}
