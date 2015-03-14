package com.yingshe.heap;

public class TreeNode{
		public TreeNode()
		{
			degree = 0;
			child = null;
			leftSibling = rightSibling = this;
			childCut = false;
			leftChild = rightChild = parent = null;
			numInLeftSubtree = 0;
			numInRightSubtree = 0;
		}
		public TreeNode(int key){
			this();
			this.key = key;
		}
		public TreeNode(int key, int identity)
		{
			this();
			this.key = key;
			this.identity = identity;
		}
		public TreeNode(int key, int identity, int neighbor){
			this(key, identity);
			this.neighbor = neighbor;
		}
		//getter and setter for "data". I define them inside the class since their logic is simple.
		public int getKey(){return key;}
		public void setKey(int _newKey){key = _newKey;}
		public int getIdentity(){return identity;}
		public void setIdentity(int identity){this.identity = identity;}
		public int getNeighbor(){return neighbor;}
		public void setNeighbor(int neighbor){this.neighbor = neighbor;}
		
		//below member variables are owned by Fibonacci heap
		public int degree;
		public TreeNode child;
		public TreeNode leftSibling;
		public TreeNode rightSibling;
		public boolean childCut;
		
		//below three member variables are shared by min heap and Fibonacci heap
		public int identity;
		public int key;
		public int neighbor;
		public TreeNode parent;

		//below member variables are owned by min heap
		public TreeNode leftChild;
		public TreeNode rightChild;
		public int numInLeftSubtree;
		public int numInRightSubtree;
}
