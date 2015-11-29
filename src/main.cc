#include "algorithms/basicMF.h"
#include "algorithms/basicKNN.h"
#include "algorithms/matrix/basicMF_m.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	
	basicSolver* s=new basicMF("./files/ml_1m.train",40,100000);
	s->Init();
	clock_t t1=clock();
	s->train();
	clock_t t2=clock();
	cout<<"Predict error:"<<s->predict("./files/ml_1m.test")<<endl;
	delete s;
	
	cout<<"Timing:"<<(double)(t2-t1)/CLOCKS_PER_SEC<<endl;
	/*basicSolver* p=new basicKNN("./files/ml_1m.train");
	p->Init();
	p->train();
	cout<<"Predict error:"<<p->predict("./files/ml_1m.test")<<endl;
	delete p;*/
	//Eigen::initParallel();
	basicSolver_m* q=new basicMF_m("./files/ml_1m.train",40,100000);
	q->Init();
	clock_t t3=clock();
	q->train();
	clock_t t4=clock();
	cout<<"Predict error:"<<q->predict("./files/ml_1m.test")<<endl;
	delete q;
	
	cout<<"Timing:"<<(double)(t4-t3)/CLOCKS_PER_SEC<<endl;
	return 0;
}
