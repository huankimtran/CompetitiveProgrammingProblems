/*Given a non-empty array of integers, return the k most frequent elements.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
Note:

You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/
/*		Algorithm Explaination
Use a DoublyLinkedList to hold the rank
Each element in rank list contains the occurence of items in that rank (All item in a rank have the same occurence) and also the items themself
Do one pass through the given array, at each iterration, increase the occurence of the item and adjust the position of the item in the rank table.
All operation is O(1) time complexity, no random access needed since items are only added to front of the back or deleted.
Time complexity in worst case is O(n)
*/
#include "iostream"
#include "unordered_map"
#include "vector"
#include "utility"
using namespace std;
template <typename T>
class Node
{
    public:
        Node<T> *left;
        Node<T> *right;
        T data;

        Node(T data,Node<T>* left,Node<T>* right)
        {
            this->data=data;
            this->left=left;
            this->right=right;
        }
};
template <typename U>
class DoublyLinkedList {
    //   head=>><1>==><2>==>head
    public:
        Node<U> *head;
        int size;
        DoublyLinkedList()
        {
            head= new Node<U>(U(),NULL,NULL);
            head->right=head;
            head->left=head;
            size=0;
        }
        void push(U e)
        {
            addRight(head,e);
        }
        void addLeft(Node<U>* n,U e)
        {
            n->left=n->left->right=new Node<U>(e,n->left,n);
            size++;
        }
        void addRight(Node<U>* n,U e)
        {
            n->right=n->right->left=new Node<U>(e,n,n->right);
            size++;
        }
        bool isTop(Node<U>* n)
        {
            return n->left==head;
        }
        Node<U>* remove(Node<U>* n)
        {
            n->left->right=n->right;
            n->right->left=n->left;
            if(n!=head)
            {
                n->left=NULL;
                n->right=NULL;                    
            }
            this->size--;
            return n;
        }
};
typedef pair<int,DoublyLinkedList<int>> LeadboardNode;   //pair<occurence,elements> data
typedef Node<int> RankListElement;   //Node<element>
//con.first = occurence
//con.second=pair<rank,positionInrank>
//con.second.first->data.first=rank's occurence
//con.second.first->data.second=rank's element list
//leaderBoardNode.second=ElementList
class Solution {
    public:
        vector<int> topKFrequent(vector<int>& nums, int k) {
            unordered_map<int,pair<int,pair<Node<LeadboardNode>*,RankListElement*>>> con;  //unordered_map<element,pair<occurence,pair<rank,positionIntheRankList>>>
            DoublyLinkedList<LeadboardNode> leaderBoard;   ////Position = rank;
            pair<int,pair<Node<LeadboardNode>*,RankListElement*>>* it;
            //add first element
            LeadboardNode* tmpO=new LeadboardNode();
            //Then add it to the new rank
            tmpO->first=1;      //set Occurence of the new rank equals to the current element
            tmpO->second.push(nums[0]) ;                //Push the current element to the new rank list
            leaderBoard.push(*tmpO);               //Add the new rank to the leaderboard as a higher rank comparing
            //Update the data of the current element
            it=&con[nums[0]];
            it->second.first=leaderBoard.head->right;            //update its rank
            it->second.second=leaderBoard.head->right->data.second.head->right;     //Update its position in the rank            
            it->first=1;
            //Iterate through array
            for(int i=1;i<nums.size();++i)
            {
                it=&(con[nums[i]]);
                it->first++; //increase occurence
                if(it->first>1)//Is this a new unique value, >1 means no?
                {
                    if(leaderBoard.isTop(it->second.first))   //if the element is in the first rank
                    {
                        if(it->second.first->data.second.size!=1)  //This rank has more than one element?, !=1 means yes
                        {
                            //First remove the element out of the current rank
                            it->second.first->data.second.remove(it->second.second);
                            //Create a new rank
                            LeadboardNode* tmp=new LeadboardNode();
                            //Then add it to the new rank
                            tmp->first=it->first;      //set Occurence of the new rank equals to the current element
                            tmp->second.push(nums[i]) ;                //Push the current element to the new rank list
                            leaderBoard.push(*tmp);               //Add the new rank to the leaderboard as a higher rank comparing
                            //Update the data of the current element
                            it->second.first=leaderBoard.head->right;            //update its rank
                            it->second.second=leaderBoard.head->right->data.second.head->right;     //Update its position in the rank
                        }
                        else    //This rank has only one element
                        {
                            //increase the rank's occurrence
                            it->second.first->data.first++;
                        }
                    }
                    else    //The elemenent is not in the first rank
                    {
                        if(it->first==it->second.first->left->data.first)    //If the element occurence equals to the higher rank
                        {
                            //Remove the element out of the current rank
                            it->second.first->data.second.remove(it->second.second);
                            //and add it to the next higher rank
                            it->second.first->left->data.second.push(nums[i]);
                            //Save the handle to the current rank before updating the elemenent
                            auto save=it->second.first;
                            //Save changes into the current element
                            it->second.first=it->second.first->left;    //Update rank
                            it->second.second=it->second.first->data.second.head->right;  //Update position
                            if(!save->data.second.size)    //if the current rank became empty, remove the rank
                            {
                                leaderBoard.remove(save);
                            }
                        }
                        else    //the element occurence is smaller than the higher rank
                        {
                            if(it->second.first->data.second.size==1)   //The rank has only one element
                            {
                                //Incrase the rank occurence
                                it->second.first->data.first++;
                            }
                            else    //The rank has more than 1 element
                            {
                                //First remove the element out of the current rank
                                it->second.first->data.second.remove(it->second.second);
                                //Create a new rank
                                LeadboardNode* tmp=new LeadboardNode();
                                //Then add it to the new rank
                                tmp->first=it->first;      //set Occurence of the new rank equals to the current element
                                tmp->second.push(nums[i]) ;                //Push the current element to the new rank list
                                leaderBoard.addLeft(it->second.first,*tmp);               //Add the new rank to the leaderboard as a higher rank comparing
                                //Update the data of the current element
                                it->second.first=it->second.first->left;    //Update rank
                                it->second.second=it->second.first->data.second.head->right;  //Update position
                            }
                        }
                    }
                }
                else    //if this is a new value
                {
                    //Add it to the last rank
                    if(leaderBoard.head->left->data.first==1)  //if occurence of last rank is 1
                    {
                        //Add this new element to this rank
                        leaderBoard.head->left->data.second.push(nums[i]);
                        //Save changes to the element 
                        it->second.first=leaderBoard.head->left;   //update the rank
                        it->second.second=leaderBoard.head->left->data.second.head->right;  //update position
                    }
                    else    //if last rank does not have occurence of 1
                    {
                        //Create a new rank
                        LeadboardNode* tmp=new LeadboardNode();
                        //Then add it to the new rank
                        tmp->first=1;      //set Occurence of the new rank equals to the current element
                        tmp->second.push(nums[i]) ;                //Push the current element to the new rank list
                        leaderBoard.addLeft(leaderBoard.head,*tmp);               //Add the new rank to the leaderboard as the lowest rank
                        //Update the data of the current element
                        it->second.first=leaderBoard.head->left;   //update the rank
                        it->second.second=leaderBoard.head->left->data.second.head->right;  //update position
                    }
                }
                //cout<<leaderBoard.head->right->data.first<<endl;
            }
            vector<int> result;
            auto itRank=leaderBoard.head->right;
            auto itRankElement=itRank->data.second.head->right;
            for(;k>0;)
            {
                for(;k>0;)
                {
                    --k;
                	// cout<<k<<endl;
                	// cout<<itRank->data.first<<endl;
                    result.push_back(itRankElement->data);
                    itRankElement=itRankElement->right;
                    if(itRankElement==itRank->data.second.head)
                        break;
                }
                itRank=itRank->right;
                itRankElement=itRank->data.second.head->right;
                
            }
            return result;
        }
};
int main()
{
	Solution a;
	int c[]={1,2,3,1,2,1,2,3,4};
	vector<int> b(begin(c),end(c));
	auto rs=a.topKFrequent(b, 4);
	for(auto it=rs.begin();it!=rs.end();++it)
	{
		cout<<*it<<" ";
	}
}