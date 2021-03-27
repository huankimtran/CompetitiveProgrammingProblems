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
void readInput(string& x, int& CJ, int& JC)
{
	cin >> CJ;
	cin >> JC;
	cin >> x;
}
template <typename T>
void printOutput(T output,int TestCaseNum)
{
	cout<<"Case #"<<TestCaseNum<<": "<<output<<endl;
}
int64_t solve(string& s, int& CJ, int& JC)
{
	// Right pass
	for(int i = 1; i < s.size(); i++)
	{
		if(s[i] == '?' && s[i-1] != '?')
		{
			s[i] = s[i-1];
		}
		
	}
	// Left pass
	for(int i = s.size() - 2; i >= 0; i--)
	{
		if(s[i] == '?' && s[i+1] != '?')
		{
			s[i] = s[i+1];
		}
	}
	// still ?
	if(s[0] == '?')
	{
		fill(s.begin(), s.end(), 'C');
	}
	// Find cost
	int cost = 0;
	for(int i = 0; i < s.size()-1; i++)
	{
		if(s[i] == 'C' && s[i+1] == 'J')
		{
			cost += CJ;
		}
		else if(s[i] == 'J' && s[i+1] == 'C')
		{
			cost += JC;
		}
	}
	return cost;
}
int main(){
	int T;
	cin>>T;
	int X, Y, cost;
	string s;
	for(int i = 0 ; i < T; i++)
	{
		readInput(s, X, Y);
		cost = solve(s, X, Y);
		printOutput(cost, i+1);
	}
	return 0;
}
