/*** Functions ***/
#include<algorithm>
#include<functional> // for hash
#include<climits> // all useful constants
#include<cmath>
#include<cstdio>
#include<cstdlib> // random
#include<ctime>
#include<iostream>
#include<sstream>
#include<iomanip> // right justifying std::right and std::setw(width)
/*** Data Structure ***/
#include<deque> // double ended queue
#include<list>
#include<queue> // including priority_queue
#include<stack>
#include<string>
#include<vector>

using namespace std;

typedef pair<int, double> InputType;

void readInput(vector<InputType>& x)
{
	std::string line;
	int R;
	double S;
	while (std::getline(std::cin, line))
	{
		istringstream r(line);
		r>>R;
		r>>S;
		x.push_back(InputType(R,S));
	}
}
template <typename T>
void printOutput(T output,int TestCaseNum)
{
	cout<<"Case #"<<TestCaseNum<<": "<<output<<endl;
}

double maxspeed(int R, double S)
{
	return sqrt(R*(S+0.16)/0.067);
}

void solve(vector<InputType> x)
{
	for (unsigned i = 0; i < x.size(); i++)
	{
		cout << (int) round(maxspeed(x[i].first, x[i].second)) <<endl;
	}
}
int main(){
	vector<InputType> in;
	readInput(in);
	solve(in);
	return 0;
}
