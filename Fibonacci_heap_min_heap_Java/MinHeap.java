package com.yingshe.heap.minheap;

import com.yingshe.heap.*;
import java.util.*;
import java.lang.*;


public class MinHeap implements IHeap
{

	public MinHeap(){root = null;}
	public MinHeap(TreeNode root){this.root = root;}
	//we do insertion top-down (not like what we learn in class which is bottom-up), we compare this "singleNode" with root,
	//then either replace root or go down itself; if go down, we will use "numInLeftSubtree" and "numInRightSubtree" to choose either
	//go to left or right. We do this because we want to keep the whole tree as balanced as possible.
	//There is a reason why I didn't insert bottom-up: for a min tree, it is hard to maintain the last node of the whole tree.
	//Change the "numInLeftSubtree" and "numInRightSubtree" accordingly during the top-down path.
	public void insert(TreeNode singleNode){
		if(root == null)
		{root = singleNode; return;}
		
		//if the original min heap is not empty, we do insert top-down
		//we use "numInLeftSubtree" and "numInRightSubtree" to guide
		//our down path, our goal is try to make the tree as balanced as possible
		TreeNode current = root;
		TreeNode parent = null; //current's parent is null
		boolean currentNodeIsLeft = false; //for root node, it has no parent, so "true" can also use here
		
		while(current != null)
		{
			//if smaller, then singleNode should replace the position of current node and use current to 
			//compare top-down
			if(singleNode.key < current.key)
			{
				//below function just handle the "link" between nodes
				exchangeTreeNodeWithSingleNode(current, singleNode, currentNodeIsLeft);
				TreeNode tmp = current;
				current = singleNode;
				singleNode = tmp;
				current.numInLeftSubtree = singleNode.numInLeftSubtree;
				current.numInRightSubtree = singleNode.numInRightSubtree;
				singleNode.numInLeftSubtree = singleNode.numInRightSubtree = 0;
			}
			//now try to push the "singleNode" down( the single node may be
			// the original one, or a node already in the tree which is exchanged
			//out )
			if(current.numInLeftSubtree <= current.numInRightSubtree)
			{
				//try to put the single node in current's left sub tree
				current.numInLeftSubtree++;
				parent = current;
				current = current.leftChild;
				currentNodeIsLeft = true;
			}
			else
			{
				//try to put the single node in current's right sub tree
				current.numInRightSubtree++;
				parent = current;
				current = current.rightChild;
				currentNodeIsLeft = false;
			}
		}
		//when "current==null" then "while" break out, we are sure "parent" is not null
		//so try to put "singleNode" as a child of "parent"
		if(currentNodeIsLeft)
		{
			parent.leftChild = singleNode;
			singleNode.parent = parent;
		}
		else
		{
			parent.rightChild = singleNode;
			singleNode.parent = parent;
		}
	}
	
	
	//this function only return the root, it won't delete the root
	public TreeNode getMin()
	{ return root;}
	
	
	//if there are nodes in the min heap, return true , otherwise return false. 
	//After a successfully delete of the root, we will adjust top-down (unlike what we have learned in class: 
	//get the last node, put it in the root position, then adjust top-down), we won't first get the last node and 
	//put it in the root position, we just directly compare root's two children and get the smallest one up, 
	//continuing adjust like this. Also don't forget change "numInLeftSubtree" and "numInRightSubtree" during the top-down path
	public boolean removeMin()
	{
		
		if(isEmpty()) return false;
		if(root.leftChild == null && root.rightChild == null)
		{
			root = null;
			return true;
		}
		
		//now more than one node in the original min heap
		TreeNode parent = root;
		boolean parentIsLeft = false;
		TreeNode child = null;
		boolean childIsLeft = false;
		int count = 0;
		while(parent.leftChild != null || parent.rightChild != null)
		{
			TreeNode left = parent.leftChild;
			TreeNode right = parent.rightChild;
			if(left != null && right != null)
			{
				if(left.key <= right.key)//exchange "left" with "parent"
				{
					childIsLeft = true;
					exchangeParentChildNode(parent, left, parentIsLeft, childIsLeft);
					TreeNode tmp = parent;
					parent = left;
					left = tmp;
					int t = parent.numInLeftSubtree;
					parent.numInLeftSubtree = left.numInLeftSubtree;
					left.numInLeftSubtree = t;
					t = parent.numInRightSubtree;
					parent.numInRightSubtree = left.numInRightSubtree;
					left.numInRightSubtree = t;
					//don't forget subtract 1 from parent.numInLeftSubtree since eventually we need to delete the one node in 
					//left sub tree
					parent.numInLeftSubtree--;
					//now update corresponding reference
					parent = left;
					parentIsLeft = true;
				}
				else
				{
					childIsLeft = false;
					exchangeParentChildNode(parent, right, parentIsLeft, childIsLeft);
					TreeNode tmp = parent;
					parent = right;
					right = tmp;
					int t = parent.numInLeftSubtree;
					parent.numInLeftSubtree = right.numInLeftSubtree;
					right.numInLeftSubtree = t;
					t = parent.numInRightSubtree;
					parent.numInRightSubtree = right.numInRightSubtree;
					right.numInRightSubtree = t;
					//don't forget subtract 1 from parent.numInRightSubtree
					parent.numInRightSubtree--;
					//now update corresponding references
					parent = right;
					parentIsLeft = false;
				}
			}
			else if(left != null)//can only exchange "parent" with "left child"
			{
				childIsLeft = true;
				exchangeParentChildNode(parent, left, parentIsLeft, childIsLeft);
				TreeNode tmp = parent;
				parent = left;
				left = tmp;
				int t = parent.numInLeftSubtree;
				parent.numInLeftSubtree = left.numInLeftSubtree;
				left.numInLeftSubtree = t;
				t = parent.numInRightSubtree;
				parent.numInRightSubtree = left.numInRightSubtree;
				left.numInRightSubtree = t;
				//don't forget subtract 1 from parent.numInLeftSubtree
				parent.numInLeftSubtree--;
				//now update corresponding references
				parent = left;
				parentIsLeft = true;
			}
			else if(right != null)
			{
				childIsLeft = false;
				exchangeParentChildNode(parent, right, parentIsLeft, childIsLeft);
				TreeNode tmp = parent;
				parent = right;
				right = tmp;
				int t = parent.numInLeftSubtree;
				parent.numInLeftSubtree = right.numInLeftSubtree;
				right.numInLeftSubtree = t;
				t = parent.numInRightSubtree;
				parent.numInRightSubtree = right.numInRightSubtree;
				right.numInRightSubtree = t;
				//don't forget subtract 1 from parent.numInRightSubtree
				parent.numInRightSubtree--;
				//now update corresponding references
				parent = right;
				parentIsLeft = false;
			}
			else
				break;
		}
		//now we need to delete node, be careful to keep links right
		if(parentIsLeft)
			parent.parent.leftChild = null;
		else
			parent.parent.rightChild = null;
		return true;
	}
	
	//If we didn't make any change to the node structure, then function "decreaseKey(...)" will be very
	// hard to implement (Maybe it seems easy to implement, just exchange parent node with child node if 
	// child node key is smaller then parent node key, use the function "exchangeParentChildNode(...)". But in
	// fact, "exchangeParentChildNode(...)" need to know the leftness of parent node and child node, and we won't
	// know leftness of parent node and child node just from a reference to child node)
	// But after we add "identity" for each node, we can easily tell whether A node is B node's left child or right child.
	// If success in decreasing key, return true; otherwise return false
	//don't forget change the "numInLeftSubtree" and "numInRightSubtree" during the process
	public boolean decreaseKey(TreeNode theNode, int _newKey)
	{
		if(theNode == null || theNode.key <= _newKey) return false;
		
		theNode.key = _newKey;
		if(theNode.parent == null) //this means "theNode" is already the "root"
			return true;
		
		TreeNode parent = theNode.parent;
		TreeNode child = theNode;
		while(parent != null && parent.key > child.key)
		{
			boolean parentIsLeft = false;
			boolean childIsLeft = false;
			if(parent.parent != null)
			{
				if(parent.parent.leftChild != null && parent.parent.leftChild.identity == parent.identity)
					parentIsLeft = true;
				else
					parentIsLeft = false;
			}
			//if "parent.parent == null" parentIsLeft could be either false or true
			if(parent.leftChild != null && parent.leftChild.identity == child.identity)
				childIsLeft = true;
			else
				childIsLeft = false;
				
			//now exchange
			exchangeParentChildNode(parent, child, parentIsLeft, childIsLeft);
			TreeNode tmp = parent;
			parent = child;
			child = tmp;
			int t = parent.numInLeftSubtree;
			parent.numInLeftSubtree = child.numInLeftSubtree;
			child.numInLeftSubtree = t;
			t = parent.numInRightSubtree;
			parent.numInRightSubtree = child.numInRightSubtree;
			child.numInRightSubtree = t;
			
			//now update corresponding pointers
			child = parent;
			parent = parent.parent;
		}
		return true;
	}
	
	
	//tell whether this min tree is empty tree or not
	public boolean isEmpty(){return root == null;}
	
	
	//this function only change corresponding "links" between nodes
	//this function exchange two nodes, "treeNode" is in this current min tree, singleNode is a single node
	// "treeNodeIsLeft" tells us whether "treeNode" is his parent's left child or right child
	// if "treeNode" is the "root", I set "treeNodeIsLeft" to "false" (true is also acceptable)
	//NOTE: for this function, "treeNode" may be the "root", so please remember update the "root" if necessary
	private boolean exchangeTreeNodeWithSingleNode(TreeNode treeNode, TreeNode singleNode, boolean treeNodeIsLeft)
	{
		if(treeNode == null || singleNode == null) return false;
		//update "parent" link for "singleNode"
		singleNode.parent = treeNode.parent;
		if(treeNode.parent != null)
		{
			if(treeNodeIsLeft)
				treeNode.parent.leftChild = singleNode;
			else
				treeNode.parent.rightChild = singleNode;
		}
		//update "leftChild" link for "singleNode"
		singleNode.leftChild = treeNode.leftChild;
		if(treeNode.leftChild != null)
			treeNode.leftChild.parent = singleNode;
		//update "rightChild" link for "singleNode"
		singleNode.rightChild = treeNode.rightChild;
		if(treeNode.rightChild != null)
			treeNode.rightChild.parent = singleNode;
		
		//update "links" for "treeNode"
		treeNode.parent = treeNode.leftChild = treeNode.rightChild = null;
		
		//update "root" if necessary
		if(singleNode.parent == null)
			root = singleNode;
		
		return true;
	}
	
	//this function only change corresponding "links" between nodes.
	//this function exchange two nodes, "parent" is the direct parent of "child", "childNodeIsLeft" denote whether
	// "child" is the left child of "parent" or not
	// Be careful with "root" node, we should change "root" value is necessary
	private boolean exchangeParentChildNode(TreeNode parent, TreeNode child, boolean parentNodeIsLeft, boolean childNodeIsLeft)
	{
		if(parent == null || child == null) return false;
		
		//update parent link for two nodes
		child.parent = parent.parent;
		if(parent.parent != null)
		{
			if(parentNodeIsLeft)
				parent.parent.leftChild = child;
			else
				parent.parent.rightChild = child;
		}
		
		if(childNodeIsLeft)
		{
			TreeNode tmp = parent.rightChild;
			parent.rightChild = child.rightChild;
			child.rightChild = tmp;
			if(tmp != null)
				tmp.parent = child;
			if(parent.rightChild != null)
				parent.rightChild.parent = parent;
			
			parent.leftChild = child.leftChild;
			if(child.leftChild != null)
				parent.leftChild.parent = parent;
				
			//now update links between "child" and "parent"
			child.leftChild = parent;
			parent.parent = child;
		}
		else
		{
			TreeNode tmp = parent.leftChild;
			parent.leftChild = child.leftChild;
			child.leftChild = tmp;
			if(parent.leftChild != null)
				parent.leftChild.parent = parent;
			if(tmp != null)
				tmp.parent = child;
				
			parent.rightChild = child.rightChild;
			if(parent.rightChild != null)
				parent.rightChild.parent = parent;
				
			//now update links between "parent" and "child"
			parent.parent = child;
			child.rightChild = parent;
		}
		
		//update "root" if necessary
		if(child.parent == null)
			root = child;
		return true;
	}
	
	
	
	
	private TreeNode root;
}



