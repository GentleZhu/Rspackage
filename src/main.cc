//#include "algorithms/basicMF.h"
#include "algorithms/basicKNN.h"
//#include "algorithms/matrix/basicMF_m.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	/*basicSolver* s=new basicMF("ua.base",40);
	s->Init();
	s->train();
	cout<<"Predict error:"<<s->predict("ua.test")<<endl;
	delete s;*/
	basicSolver* s=new basicKNN("ua.base");
	s->Init();
	s->train();
	cout<<"Predict error:"<<s->predict("ua.test")<<endl;
	delete s;
	/*rating a=rating();
	cout<<a.Init("ua.base")<<endl;
	cout<<a.getUsercount()<<" "<<a.getItemcount()<<endl;*/
	/*ifstream fin;
	int u_id,i_id,rt,tm;
	fin.open("ua.base");
	while(!fin.eof()){
		fin>>u_id>>i_id>>rt>>tm;
		cout<<"input"<<rt<<"output"<<a.getRating(u_id,i_id)<<endl;
	}*/
	return 0;
}