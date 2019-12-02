/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <cmath>
using namespace std;
class Solution 
{
    public:
        bool isPrime(int n)
        {
            if(n<=1)
                return false;
            else
            {
                for(int i=sqrt(n);i>1;i--)
                {
                    if(n%i==0)
                        return false;
                }
                return true;
            }
        }
        bool repeatedSubstringPattern(string s) 
        {
            bool good;
            int subLength,lastI;
            for(int i=ceil(sqrt(s.size()));i>1;i--)
            {
                if(s.size()%i==0)
                {
        			if(this->isPrime(i))
        			{
                        subLength=s.size()/i;
                        good=true;                    
                        for(int pos=0;pos<subLength;pos++)
                        {
                            for(int rep=1;rep<i;rep++)
                                if(s[pos]!=s[pos+rep*subLength])
                                {
                                    good=false;
                                    break;
                                }
                            if(!good)
                                break;
                        }
                        if(good)
                            return true;		
        			}
                    lastI=i;
                    i=s.size()/i;
        			if(this->isPrime(i))
        			{
                        subLength=s.size()/i;
                        good=true;                    
                        for(int pos=0;pos<subLength;pos++)
                        {
                            for(int rep=1;rep<i;rep++)
                                if(s[pos]!=s[pos+rep*subLength])
                                {
                                    good=false;
                                    break;
                                }
                            if(!good)
                                break;
                        }
                        if(good)
                            return true;		
        			}
                    i=lastI;
                }
    		}
        }
};
int main()
{
    Solution a;
    bool e=a.repeatedSubstringPattern("aaaaab");
    cout<<(e?"Yes":"No");
    return 0;
}