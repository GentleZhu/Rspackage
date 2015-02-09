//#include "data/rating.cc"
#include "algorithms/basicMF.cc"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	basicSolver* s=new basicMF("ua.base");
	s->train();
	//rating a=rating();
	//cout<<a.Init("ua.base")<<endl;
	//cout<<a.getUsercount()<<" "<<a.getItemcount()<<endl;
	return 0;
}