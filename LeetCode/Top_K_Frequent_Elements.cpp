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
class DoublyLinkedList
{
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
            //add first element
            LeadboardNode* tmpO=new LeadboardNode();
            //Then add it to the new rank
            tmpO->first=1;      //set Occurence of the new rank equals to the current element
            tmpO->second.push(nums[0]) ;                //Push the current element to the new rank list
            leaderBoard.push(*tmpO);               //Add the new rank to the leaderboard as a higher rank comparing
            //Update the data of the current element
            con[nums[0]].second.first=leaderBoard.head->right;            //update its rank
            con[nums[0]].second.second=leaderBoard.head->right->data.second.head->right;     //Update its position in the rank            
            //Iterate through array
            for(int i=1;i<nums.size();++i)
            {
                con[nums[i]].first++; //increase occurence
                if(con[nums[i]].first>1)//Is this a new unique value, >1 means no?
                {
                    if(leaderBoard.isTop(con[nums[i]].second.first))   //if the element is in the first rank
                    {
                        if(con[nums[i]].second.first->data.second.size!=1)  //This rank has more than one element?, !=1 means no
                        {
                            //First remove the element out of the current rank
                            con[nums[i]].second.first->data.second.remove(con[nums[i]].second.second);
                            //Create a new rank
                            LeadboardNode* tmp=new LeadboardNode();
                            //Then add it to the new rank
                            tmp->first=con[nums[i]].first;      //set Occurence of the new rank equals to the current element
                            tmp->second.push(nums[i]) ;                //Push the current element to the new rank list
                            leaderBoard.push(*tmp);               //Add the new rank to the leaderboard as a higher rank comparing
                            //Update the data of the current element
                            con[nums[i]].second.first=leaderBoard.head->right;            //update its rank
                            con[nums[i]].second.second=leaderBoard.head->right->data.second.head->right;     //Update its position in the rank
                        }
                        else    //This rank has only one element
                        {
                            //increase the rank's occurrence
                            cout<<i<<endl;
                            con[nums[i]].second.first->data.first++;
                        }
                    }
                    else    //The elemenent is not in the first rank
                    {
                        if(con[nums[i]].first==con[nums[i]].second.first->left->data.first)    //If the element occurence equals to the higher rank
                        {
                            //Remove the element out of the current rank
                            con[nums[i]].second.first->data.second.remove(con[nums[i]].second.second);
                            //and add it to the next higher rank
                            con[nums[i]].second.first->left->data.second.push(nums[i]);
                            //Save changes into the current element
                            con[nums[i]].second.first=con[nums[i]].second.first->left;    //Update rank
                            con[nums[i]].second.second=con[nums[i]].second.first->data.second.head->left;  //Update position
                        }
                        else    //the element occurence is smaller than the higher rank
                        {
                            //First remove the element out of the current rank
                            con[nums[i]].second.first->data.second.remove(con[nums[i]].second.second);
                            //Create a new rank
                            LeadboardNode* tmp=new LeadboardNode();
                            //Then add it to the new rank
                            tmp->first=con[nums[i]].first;      //set Occurence of the new rank equals to the current element
                            tmp->second.push(nums[i]) ;                //Push the current element to the new rank list
                            leaderBoard.addLeft(con[nums[i]].second.first,*tmp);               //Add the new rank to the leaderboard as a higher rank comparing
                            //Update the data of the current element
                            con[nums[i]].second.first=con[nums[i]].second.first->left;    //Update rank
                            con[nums[i]].second.second=con[nums[i]].second.first->data.second.head->left;  //Update position
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
                        con[nums[i]].second.first=leaderBoard.head->left;   //update the rank
                        con[nums[i]].second.second=leaderBoard.head->left->data.second.head->left;  //update position
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
                        con[nums[i]].second.first=leaderBoard.head->left;   //update the rank
                        con[nums[i]].second.second=leaderBoard.head->left->data.second.head->left;  //update position
                    }
                }
                //cout<<leaderBoard.head->right->data.first<<endl;
            }
            vector<int> result;
            for(;k>0;)
            {
                auto itRank=leaderBoard.head->right;
                auto itRankElement=itRank->data.second.head->right;
                for(int i=k;i>0;k=--i)
                {
                    result.push_back(itRankElement->data);
                    itRankElement=itRankElement->right;
                    if(itRankElement==itRank->data.second.head)
                        break;
                }
                itRank=itRank->right;
                
            }
            return result;
        }
};
