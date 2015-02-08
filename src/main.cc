#include "data/rating.cc"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	rating a=rating();
	cout<<a.Init("ua.base")<<endl;
	cout<<a.getUsercount()<<" "<<a.getItemcount()<<endl;
	return 0;
}