/*
Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.

 

Example 1:

Input: "abab"
Output: True
Explanation: It's the substring "ab" twice.
Example 2:

Input: "aba"
Output: False
Example 3:

Input: "abcabcabcabc"
Output: True
Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)


=======================Solution_Idea====================================
string s="abcdabcdabcd"
Possible                   String if the sub length is right 
sub string length
1                               aaaaaaaaaaaa
4                               abcdabcdabcd   (Correct)
6                               abcdababcdab
so true

string s="abcccc"
Possible                   String if the sub length is right 
sub string length
1                               aaaaaa
2                               ababab  
3                               abcabc
None is right so false

if s is a repeated substring, then 
Length(s)=length(largest_sub_string_for_repeating)*prime
*/
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        const int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
        const int NUM_PRIME=25;
        int length=s.size();
        vector<int> posLength;
        
        if(length<=1)
            return false;
        posLength.push_back(1);
        for(int i=0;i<NUM_PRIME;i++)
        {
            if(length%prime[i]==0)
                if(length==prime[i])
                    break;
                else
                    posLength.push_back(length/prime[i]);
        }
        vector<int>::iterator it;
        for(int i=0;i<length;i++)
        {
            for(it=posLength.begin();it!=posLength.end();)
            {
                if(s[i]!=s[i%(*it)])
                    it=posLength.erase(it);
                else
                    ++it;
            }
            if(posLength.size()==0)
                return false;
        }
        return true;
    }
};