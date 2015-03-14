package com.yingshe.heap;

public interface IHeap
{
	abstract public void insert(TreeNode singleNode);
	abstract public TreeNode getMin();
	abstract public boolean removeMin();
	abstract public boolean decreaseKey(TreeNode theNode, int _newKey);
	abstract public boolean isEmpty();
}