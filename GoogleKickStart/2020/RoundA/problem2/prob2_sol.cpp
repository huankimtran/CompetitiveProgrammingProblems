#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std; 
#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
inline bool EQ(double a, double b) { return fabs(a-b) < 1e-9; }
const int INF = 1<<29;
typedef long long ll;
inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }
template<class T> void chmax(T & a, const T & b) { a = max(a, b); }
template<class T> void chmin(T & a, const T & b) { a = min(a, b); }
/////////////////////////////////////////////////////////////////////
class thePlate
{
    public:
        int beauty;
        int iStack;
        thePlate()
        {
            this->beauty=0;
            this->iStack=0;
        }
        thePlate(int beauty,int iStack)
        {
            this->beauty=beauty;
            this->iStack=iStack;
        }
        bool operator<(const thePlate b)
        {
            return this->beauty<b.beauty;
        }

        bool operator() (const thePlate& lhs, const thePlate& rhs) const
        {
            return lhs.beauty<rhs.beauty;
        }
};
int findMaxSum(vector<queue<int>> sDisk,int P)
{
    priority_queue<thePlate,vector<thePlate>,thePlate> q;
    int beauty;
    int sum=0;
    thePlate aPlate;
    for(int i=0;i<sDisk.size();i++)
    {
        beauty=sDisk[i].front();
        sDisk[i].pop();
        q.push(thePlate(beauty,i));
    }
    do
    {
        aPlate=q.top();
        q.pop();
        sum+=aPlate.beauty;
        P--;
        cout<<"Get out "<<aPlate.beauty<<" from "<<aPlate.iStack<<endl;
        if(sDisk[aPlate.iStack].size())
        {
            aPlate.beauty=sDisk[aPlate.iStack].front();
            sDisk[aPlate.iStack].pop();
            q.push(aPlate);
        }
    }while(P>0);
    return sum;
}
int main()
{
    int T,N,K,P,tmp,rs;
    vector<queue<int>> A;
    cin>>T;
    for(int i=0;i<T;i++)
    {
        A.clear();
        cin>>N;
        cin>>K;
        cin>>P;
        for(int j=0;j<N;j++)
        {
            A.emplace_back();
            for(int k=0;k<K;k++)
            {
                cin>>tmp;
                A.back().push(tmp);
            }
        }
        rs=findMaxSum(A,P);
        cout<<"Case #"<<i+1<<": "<<rs<<endl;
    }
    return 0;
}