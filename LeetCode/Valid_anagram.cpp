/*
 * Given two strings s and t , write a function to determine if t is an anagram of s.
 * Example 1:
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 * Example 2:
 * Input: s = "rat", t = "car"
 * Output: false
 * Note:
 * You may assume the string contains only lowercase alphabets.
 * Follow up:
 * What if the inputs contain unicode characters? How would you adapt your solution to such case?
 * */
class Solution {
	public:
		bool isAnagram(string s, string t) {
			if(s.size() != t.size())
				return false;
			else
			{
			unordered_map<char,unsigned int> con;
										            int check=0,tmp;
											                for(int i=0;i<s.size();i++)
														            i
																                    ++con[s[i]]||con.erase(s[i]);
																		                    --con[t[i]]||con.erase(t[i]);
																				                }
													            return con.size()==0;
														            }
					        }
};
