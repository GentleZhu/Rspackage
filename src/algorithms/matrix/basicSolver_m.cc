#include "basicSolver_m.h"

basicSolver_m::basicSolver_m(const char* inputFile){
	data=new rating_m();
	data->Init(inputFile);
}

basicSolver_m::~basicSolver_m(){
	delete data;
}
