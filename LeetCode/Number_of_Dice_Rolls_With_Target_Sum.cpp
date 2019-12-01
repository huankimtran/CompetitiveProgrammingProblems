/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;
/*
You have d dice, and each die has f faces numbered 1, 2, ..., f.

Return the number of possible ways (out of fd total ways) modulo 10^9 + 7 to roll the dice so the sum of the face up numbers equals target.

 

Example 1:

Input: d = 1, f = 6, target = 3
Output: 1
Explanation: 
You throw one die with 6 faces.  There is only one way to get a sum of 3.
Example 2:

Input: d = 2, f = 6, target = 7
Output: 6
Explanation: 
You throw two dice, each with 6 faces.  There are 6 ways to get a sum of 7:
1+6, 2+5, 3+4, 4+3, 5+2, 6+1.
Example 3:

Input: d = 2, f = 5, target = 10
Output: 1
Explanation: 
You throw two dice, each with 5 faces.  There is only one way to get a sum of 10: 5+5.
Example 4:

Input: d = 1, f = 2, target = 3
Output: 0
Explanation: 
You throw one die with 2 faces.  There is no way to get a sum of 3.
Example 5:

Input: d = 30, f = 30, target = 500
Output: 222616187
Explanation: 
The answer must be returned modulo 10^9 + 7.
 

Constraints:

1 <= d, f <= 30
1 <= target <= 1000
*/
class Solution {
public:
    long int **dp;
    long int d,f,target;
    int numRollsToTarget(int d, int f, int target) {
        if(f*d<target)
            return 0;
        else
        {
            this->d=d;
            this->f=f;
            this->target=target;
            this->dp=new long int*[d];
            for(int i=0;i<d;i++)
                this->dp[i]=new long int[target];
            buildDPTable();
            return dp[d-1][target-1];
        }
            
    }
    /*
        dp[nd][t]=sum(dp[nd-1][t-nf]):nf=1->f
        for example d=3 f=6 target=7
        given f
        d\target 1 2 3 4 5 6 7
            1    1 1 1 1 1 1 0  
            2    0 1 2 3 4 5 6
            3    0 0 1 3    
            4
            5
            .
            .
*/
    void buildDPTable() {
            for(int t=0;t<target;t++)
            {
                if(t+1<=f)
                    dp[0][t]=1;
                else
                    dp[0][t]=0;
            }
            for(int nd=1;nd<d;nd++)
            {
                for(int t=0;t<target;t++)
                {
                    if(t+1<nd+1)
                        dp[nd][t]=0;
                    else
                    {
                        if(t+1!=nd+1)
                        {
                            if(t+1<(nd+1)*f)
                            {
                                dp[nd][t]=0;
                                for(int n=1;n<=(t<f?t:f);n++)
                                    dp[nd][t]=(dp[nd][t]+dp[nd-1][((t+1)-n)-1])%1000000007;
                            }
                            else
                            {
                                if(t+1!=(nd+1)*f)
                                    dp[nd][t]=0;
                                else
                                    dp[nd][t]=1;
                            }
                        }
                        else
                        {
                            dp[nd][t]=1;
                        }
                    }
                }
            }            

    }
};
int main()
{
    Solution a;
    cout<<a.numRollsToTarget(30,30,500);

    return 0;
}

