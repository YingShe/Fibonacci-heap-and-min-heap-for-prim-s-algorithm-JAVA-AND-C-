#include "MinHeap.h"
#include <iostream>
#include <queue>
using namespace std;

//we do insertion top-down (not like we learn in class which is bottom-up), we compare this _newNode with root,
//then either replace root or go down itself; if go down, we will use "numInLeftSubtree" and "numInRightSubtree" to choose either
//go to left or right. We do this because we want to keep the whole tree as balanced as possible.
//There is a reason why I didn't insert bottom-up: for a min tree, it is hard to maintain the last node of the whole tree.
//Change the "numInLeftSubtree" and "numInRightSubtree" accordingly during the top-down path
void MinHeap::insert(TreeNode* _newNode)
{
	if(root == NULL)
	{
		root = _newNode;
		return;
	}
		
	//if the original min heap is not empty, we do insertion top-down
	TreeNode *current = root;
	TreeNode *parent = NULL;
	bool currentNodeIsLeft = false;
	while(current != NULL)
	{		
		if(_newNode->key < current->key)//then _newNode should replace the position of current and use current to compare top-down
		{
			exchangeTreeNodeWithSingleNode(current, _newNode, currentNodeIsLeft);
			current->numInLeftSubtree = _newNode->numInLeftSubtree;
			current->numInRightSubtree = _newNode->numInRightSubtree;
			_newNode->numInLeftSubtree = 0;
			_newNode->numInRightSubtree = 0;
		}
		if(current->numInLeftSubtree <= current->numInRightSubtree) // we choose to insert into left sub tree
		{
			current->numInLeftSubtree++;
			parent = current;
			current = current->leftChild;
			currentNodeIsLeft = true;
		}
		else //otherwise we choose to insert into right sub tree
		{
			current->numInRightSubtree++;
			parent = current;
			current = current->rightChild;
			currentNodeIsLeft = false;
		}
	}
	//now put the _newNode into the min tree
	if(currentNodeIsLeft)
	{
		parent->leftChild = _newNode;
		_newNode->parent = parent;
	}
	else
	{
		parent->rightChild = _newNode;
		_newNode->parent = parent;
	}
}



TreeNode* MinHeap::getMin()
{
	return root;
}



//if there are nodes in the min heap, return true , otherwise return false. 
//After a successfully deletion of the root, we will adjust top-down (unlike what we have learned in class: get the last node, put
// it in the root position, then adjust top-down), we won't first get the last node and put it in the root position, we just directly
// compare root's two children and get the smallest one, continuing adjust like this. Also don't forget change 
// "numInLeftSubtree" and "numInRightSubtree" during the top-down path
bool MinHeap::removeMin()
{
	if(root == NULL) return false;
	if(root->leftChild == NULL && root->rightChild == NULL)
	{
		delete root;
		root = NULL;
		return true;
	}
	
	TreeNode *parent = root;
	bool parentIsLeft = false;
	TreeNode *child = NULL;
	bool childIsLeft = false;
	while(parent->leftChild != NULL || parent->rightChild != NULL)
	{
		//we need to create these two variables in order to make pointers change in place
		TreeNode *left = parent->leftChild;
		TreeNode *right = parent->rightChild;
		if(left != NULL && right != NULL)
		{
			if(left->key <= right->key)
			{
				childIsLeft = true;
				exchangeParentChildNode(parent, left, parentIsLeft, childIsLeft);
				int tmp = parent->numInLeftSubtree;
				parent->numInLeftSubtree = left->numInLeftSubtree;
				left->numInLeftSubtree = tmp;
				tmp = parent->numInRightSubtree;
				parent->numInRightSubtree = left->numInRightSubtree;
				left->numInRightSubtree = tmp;
				//don't forget to subtract 1 from parent->numInLeftSubtree since left sub tree will finally lost one node 
				parent->numInLeftSubtree--;
				//now change parent
				parent = left;
				parentIsLeft = true;
			}
			else
			{
				childIsLeft = false;
				exchangeParentChildNode(parent, right, parentIsLeft, childIsLeft);
				int tmp = parent->numInLeftSubtree;
				parent->numInLeftSubtree = right->numInLeftSubtree;
				right->numInLeftSubtree = tmp;
				tmp = parent->numInRightSubtree;
				parent->numInRightSubtree = right->numInRightSubtree;
				right->numInRightSubtree = tmp;
				//don't forget to subtract 1 from parent->numInRightSubtree since right sub tree will finally lost one node
				parent->numInRightSubtree--;
				//now change parent
				parent = right;
				parentIsLeft = false;
			}
		}
		else if(left != NULL) //right is NULL, can only change with left child
		{
			childIsLeft = true;
			exchangeParentChildNode(parent, left, parentIsLeft, childIsLeft);
			int tmp = parent->numInLeftSubtree;
			parent->numInLeftSubtree = left->numInLeftSubtree;
			left->numInLeftSubtree = tmp;
			tmp = parent->numInRightSubtree;
			parent->numInRightSubtree = left->numInRightSubtree;
			left->numInRightSubtree = tmp;
			//don't forget to subtract 1 from parent->numInLeftSubtree since left sub tree will finally lost one node 
			parent->numInLeftSubtree--;
			//now change parent
			parent = left;
			parentIsLeft = true;
		}
		else if(right != NULL)
		{
			childIsLeft = false;
			exchangeParentChildNode(parent, right, parentIsLeft, childIsLeft);
			int tmp = parent->numInLeftSubtree;
			parent->numInLeftSubtree = right->numInLeftSubtree;
			right->numInLeftSubtree = tmp;
			tmp = parent->numInRightSubtree;
			parent->numInRightSubtree = right->numInRightSubtree;
			right->numInRightSubtree = tmp;
			//don't forget to subtract 1 from parent->numInRightSubtree since right sub tree will finally lost one node
			parent->numInRightSubtree--;
			//now change parent
			parent = right;
			parentIsLeft = false;
		}
		else
			break;
	}
	//now we need to delete node "parent", be careful to keep pointers correct
	if(parentIsLeft)
		parent->parent->leftChild = NULL;
	else
		parent->parent->rightChild = NULL;
	parent->parent = NULL;
	delete parent;
	
	return true;
}


//after we add "identity" for each node, we can easily tell whether A node is B node's
// left child or right child
bool MinHeap::decreaseKey(TreeNode* _theNode, int _newKey)
{
	if(_theNode == NULL) //if "_theNode" is NULL, then wrong
		return false;
	if(_theNode->key <= _newKey) //if the new key is bigger than original one, wrong
		return false;
		
	_theNode->key = _newKey; //call the setter function from class "TreeNode"
	
	if(_theNode->parent == NULL)  //if "_theNode" is already the root(only root's parent can be NULL), then no need to adjust
		return true;
	
	TreeNode* parent = _theNode->parent;
	TreeNode* child = _theNode;
	while(parent != NULL && parent->key > child->key)
	{
		bool parentIsLeft;
		bool childIsLeft;
		//first decide whether parent node is his parent node's left child or right child
		if(parent->parent != NULL)
		{
			if(parent->parent->leftChild != NULL && parent->parent->leftChild->identity == parent->identity)
				parentIsLeft = true;
			else
				parentIsLeft = false;
		}
		else
			parentIsLeft = false;

		//decide whether child node is his parent node's left child or right child
		if(parent->leftChild != NULL && parent->leftChild->identity == child->identity)
			childIsLeft = true;
		else
			childIsLeft = false;

		exchangeParentChildNode(parent, child, parentIsLeft, childIsLeft);
		int tmp = parent->numInLeftSubtree;
		parent->numInLeftSubtree = child->numInLeftSubtree;
		child->numInLeftSubtree = tmp;
		tmp = parent->numInRightSubtree;
		parent->numInRightSubtree = child->numInRightSubtree;
		child->numInRightSubtree = tmp;
		child = parent;
		parent = parent->parent;
	}
	return true;
}


//tell whether this min tree is empty tree or not
bool MinHeap::isEmpty()
{
	return root==NULL?true:false;
}


//this function exchange two nodes, "treeNode" is in this current min tree, singleNode is a single node
// "treeNodeIsLeft" tells us whether "treeNode" is his parent's left child or right child
// if "treeNode" is the "root", I set "treeNodeIsLeft" to "false"
// for this function, we only change pointers, we don't care about others
// "leftChild", "rightChild" and "parent" of "singleNode" are "NULL"
// Be careful with "root" node, we should change "root" value if necessary
bool MinHeap::exchangeTreeNodeWithSingleNode(TreeNode*& treeNode, TreeNode*& singleNode, bool treeNodeIsLeft)
{
	if(treeNode == NULL || singleNode == NULL)
		return false;
	
	singleNode->parent = treeNode->parent;
	if(treeNode->parent != NULL)
	{
		if(treeNodeIsLeft)
			treeNode->parent->leftChild = singleNode;
		else
			treeNode->parent->rightChild = singleNode;
	}
	
	singleNode->leftChild = treeNode->leftChild;
	if(treeNode->leftChild != NULL)
		treeNode->leftChild->parent = singleNode;
	
	singleNode->rightChild = treeNode->rightChild;
	if(treeNode->rightChild != NULL)
		treeNode->rightChild->parent = singleNode;
		
	treeNode->parent = treeNode->leftChild = treeNode->rightChild = NULL;
	//now we need exchange the role 
	TreeNode *tmp = singleNode;
	singleNode = treeNode;
	treeNode = tmp;
	
	//change "root" value if necessary
	if(treeNode->parent == NULL)
		root = treeNode;
		
	return true;
}



//this function exchange two nodes, "parent" is the direct parent of "child", "childNodeIsLeft" denote whether
// "child" is the left child of "parent" or "not"
// for this function, we only change pointers, we don't care about others
// Be careful with "root" node, we should change "root" value is necessary
bool MinHeap::exchangeParentChildNode(TreeNode*& parent, TreeNode*& child, bool parentNodeIsLeft, bool childNodeIsLeft)
{
	if(parent == NULL || child == NULL)
		return false;
		
	//this variable is used to keep something 
	TreeNode tmpChild = *child;
	
	child->parent = parent->parent;
	if(parent->parent != NULL)
	{
		if(parentNodeIsLeft)
			parent->parent->leftChild = child;
		else
			parent->parent->rightChild = child;
	}
	
	if(childNodeIsLeft)
	{
		child->leftChild = parent;
		child->rightChild = parent->rightChild;
		if(parent->rightChild != NULL)
			parent->rightChild->parent = child;
	}
	else
	{
		child->rightChild = parent;
		child->leftChild = parent->leftChild;
		if(parent->leftChild != NULL)
			parent->leftChild->parent = child;
	}
	parent->parent = child;
	
	parent->leftChild = tmpChild.leftChild;
	if(tmpChild.leftChild != NULL)
		tmpChild.leftChild->parent = parent;
	parent->rightChild = tmpChild.rightChild;
	if(tmpChild.rightChild != NULL)
		tmpChild.rightChild->parent = parent;
		
	//now change the role
	TreeNode *tmp = child;
	child = parent;
	parent = tmp;
	
	//change "root" value if necessary
	if(parent->parent == NULL)
		root = parent;
	return true;
}



//I write this recursive function to free space 
void MinHeap::releaseSpace(TreeNode* node)
{
	if(node == NULL) 
		return;
	TreeNode *left = node->leftChild;
	TreeNode *right = node->rightChild;
	delete node;
	releaseSpace(left);
	releaseSpace(right);
}


//this function is written for debugging, I debug the code by show the heap
//I traverse the tree in BFS manner
void MinHeap::showHeap()
{
	if(root == NULL) 
	{
		cout << "Empty tree !!!!!" << endl;
		return;
	}
	queue<TreeNode*> tool;
	tool.push(root);
	int level = 0;
	while(!tool.empty())
	{
		cout << "Level " << level << ": \n";
		int size = tool.size();
		while(size > 0)
		{
			TreeNode *tmp = tool.front(); tool.pop();
			cout << "identity " << tmp->identity << ": " << "; parent is " << (tmp->parent!=NULL?tmp->parent->identity:-1) << "; left child is " << (tmp->leftChild!=NULL?tmp->leftChild->identity:-1) << "; right child is " << (tmp->rightChild!=NULL?tmp->rightChild->identity:-1);
			cout << "; nodes in left sub tree: " << tmp->numInLeftSubtree << "; nodes in right sub tree: " << tmp->numInRightSubtree << endl;
			if(tmp->leftChild != NULL)
				tool.push(tmp->leftChild);
			if(tmp->rightChild != NULL)
				tool.push(tmp->rightChild);
			size--;
		}
		level++;
	}
}
