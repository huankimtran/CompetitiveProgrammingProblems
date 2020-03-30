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
void readInput(vector<int64_t>& x,vector<int64_t>& y)
{
	int64_t tmp;
	int n;
	x.clear();
	y.clear();
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>tmp;
		x.push_back(tmp);
	}
	for(int i=0;i<n;i++)
	{
		cin>>tmp;
		y.push_back(tmp);
	}
}
template <typename T>
void printOutput(T output,int TestCaseNum)
{
	cout<<"Case #"<<TestCaseNum<<": "<<output<<endl;
}
int64_t solve(vector<int64_t> x,vector<int64_t> y)
{
	int64_t sum=0;
	sort(x.begin(),x.end());
	sort(y.begin(),y.end(),greater<int64_t>());
	for(int i=0;i<x.size();i++)
	{
		sum+=x[i]*y[i];
	}
	return sum;
}
int main(){
	int T,n;
	vector<int64_t> x,y;
	int64_t sum;
	cin>>T;
	for(int i = 0 ; i < T; i++)
	{
		readInput(x,y);
		sum=solve(x,y);
		printOutput(sum,i+1);
	}
	return 0;
}
