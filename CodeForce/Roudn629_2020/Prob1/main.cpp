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

int main(){
	int T,a,b;
	cin>>T;
	for(int i = 0 ; i < T; i++)
	{
		cin>>a>>b;
		if(a%b)
		{
			cout<<(b-(a%b))<<endl;
		}
		else
		{
			cout<<0<<endl;
		}

	}
	return 0;
}