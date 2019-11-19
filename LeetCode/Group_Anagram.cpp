/*
 * Given an array of strings, group anagrams together.
 * Example:
 * Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
 * Output:
 * [
 *   ["ate","eat","tea"],
 *     ["nat","tan"],
 *       ["bat"]
 *       ]
 *       */
class Solution {
	public:
		    vector<vector<string>> groupAnagrams(vector<string>& strs) {
			            unordered_map<int,vector<vector<string>>> con;
				            for(auto it=strs.begin();it!=strs.end();it++)
						            {
								                vector<vector<string>> group(*it);
										            if(!group.size())
												                {
															                group.push_back((new vector()).push_back(*it));
																	            }
											                else
														            {
																                    
																               } 
													            con.erase(it++);
														            }
					            
					        }
};
