#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_

//MinHeap is a tree whose tree nodes are instantiations of class "TreeNode"
//first include "TreeNode.h"
#include "TreeNode.h"

//what action should a "min heap" provide?
//first, a min heap allows insert
//second, a min heap allows getMin
//third, a min heap allows removeMin
//fourth, a min heap allows descreaseKey for a specified node
//Of course, during perform above action, we would take care to keep the structure of a "min heap"
class MinHeap{
	public:
		//default constructor
		MinHeap(){
			root = NULL;//root default to NULL
		}
		//another overloaded constructor
		MinHeap(TreeNode* _root){
			root = _root;
		}
		//destructor for the MinHeap, do nothing
		~MinHeap(){
			releaseSpace(root);
		}
		
	public:
		//we do insertion top-down (not like what we learn in class which is bottom-up), we compare this _newNode with root,
		//then either replace root or go down itself; if go down, we will use "numInLeftSubtree" and "numInRightSubtree" to choose either
		//go to left or right. We do this because we want to keep the whole tree as balanced as possible.
		//There is a reason why I didn't insert bottom-up: for a min tree, it is hard to maintain the last node of the whole tree.
		//Change the "numInLeftSubtree" and "numInRightSubtree" accordingly during the top-down path
		void insert(TreeNode* _newNode);
		
		//this function only return the root, it won't delete the root
		TreeNode* getMin();
		
		//if there are nodes in the min heap, return true , otherwise return false. 
		//After a successfully delete of the root, we will adjust top-down (unlike what we have learned in class: get the last node, put
		// it in the root position, then adjust top-down), we won't first get the last node and put it in the root position, we just directly
		// compare root's two children and get the smallest one, continuing adjust like this. Also don't forget change 
		// "numInLeftSubtree" and "numInRightSubtree" during the top-down path
		bool removeMin(); 
		
		//if success in decreasing key, return true; otherwise return false
		//don't forget change the "numInLeftSubtree" and "numInRightSubtree" during the process
		bool decreaseKey(TreeNode* theNode, int _newKey);
	
		//tell whether this min tree is empty tree or not
		bool isEmpty();
	public: 
		void showHeap();
	private:
		bool exchangeTreeNodeWithSingleNode(TreeNode*& treeNode, TreeNode*& singleNode, bool treeNodeIsLeft);
		bool exchangeParentChildNode(TreeNode*& parent, TreeNode*& child, bool parentNodeIsLeft, bool childNodeIsLeft);
	
	private:
		//this function is used by destructor to release the space of this tree
		void releaseSpace(TreeNode* Node);
		
	private:
		TreeNode* root; //root of the min heap, default to NULL
};

#endif
