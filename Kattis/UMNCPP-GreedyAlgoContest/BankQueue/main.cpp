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

class Person
{
	public:
	int t,c;
	
	Person(int t,int c)
	{
		this->t=t;
		this->c=c;
	}
	
	Person(): t(0) , c(0)
	{}

	bool operator<(const Person& p) const
	{
		if(p.t>t)
		{
			return true;
		}
		else if(p.t==t)
		{
			return p.c > c;
		}
		else
		{
			return false;
		}
	}
};

typedef priority_queue<Person> TheQueue;

TheQueue readInput(int& T)
{
	int N,c,t;
	TheQueue q;
	cin>>N;
	cin>>T;
	for(int i=0;i<N;i++)
	{
		cin>>c>>t;
		q.emplace(t,c);
	}
	return q;
}

template <typename T>
void printOutput(T output,int TestCaseNum)
{
	cout<<"Case #"<<TestCaseNum<<": "<<output<<endl;
}

template <typename T>
void printOutput(T output)
{
	cout<<output<<endl;
}

int64_t solve(TheQueue q,int T)
{
	int64_t sum=0;
	Person now;
	while(q.size() && T)
	{	
//		cout<<T<<endl;
		now=q.top();
		while(q.size() && now.t==q.top().t)
		{
			q.pop();
		}
		sum+=now.c;
		T--;
	}
	return sum;
}
int main(){
	TheQueue q;
	int T;
	q=readInput(T);
	cout<<solve(q,T);
	return 0;
}
