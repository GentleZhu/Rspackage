#include "algorithms/basicMF.h"
#include "algorithms/basicKNN.h"
#include "algorithms/matrix/basicMF_m.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	basicSolver* s=new basicMF("ua.base",40);
	s->Init();
	s->train();
	cout<<"Predict error:"<<s->predict("ua.test")<<endl;
	delete s;
	/*basicSolver* s=new basicKNN("ua.base");
	s->Init();
	s->train();
	cout<<"Predict error:"<<s->predict("ua.test")<<endl;
	delete s;*/
	/*basicSolver_m* s=new basicMF_m("ua.base",40);
	s->Init();
	s->train();
	cout<<"Predict error:"<<s->predict("ua.test")<<endl;
	delete s;*/
	return 0;
}