package com.yingshe.heap.fiheap;

import com.yingshe.heap.*;
import java.util.*;

public class FibonacciHeap implements IHeap
{
	public FibonacciHeap(){ minimumPointer = null;}
	FibonacciHeap(TreeNode minimumPointer){this.minimumPointer = minimumPointer;}
	
	//anotherTree could be only one single node tree, or be a "min tree"
	//after insert, we will call "pariwiseCombine(...)", and in fact, we can also not call "pairwiseCombine(...)" in this "insert(...)"
	// If we call, the actual time complexity for "insert(...)" is not O(1), but O(logn). But pairwise combine make 
	// other function less amortized time complexity
	public void insert(TreeNode anotherTree)
	{
		anotherTree.parent = null;
		anotherTree.childCut = false;
		if(minimumPointer == null) //if the original Fibonacci heap is empty
		{
			minimumPointer = anotherTree;
			return;
		}
		
		//otherwise call private function to merge two circular doubly linked lists
		mergeTwoCircularLinkedList(minimumPointer, anotherTree);
		//now need to reset the minimum pointer if necessary
		if(anotherTree.key < minimumPointer.key)
			minimumPointer = anotherTree;
		
		//even actual time complexity for inserting is O(1), but we still call "pairwiseCombine(...)". we can comment 
		// this statement out and achieve the same amortized time complexity. But I include it here for personal preference
		pairwiseCombine(minimumPointer);
	}
	
	
	//anotherHeap is another Fibonacci heap (remember, a min Fibonacci heap is a collection of min tree)
	//after meld, we will call "pairwiseCombine(...)"
	// to be honest, this "meld" function is almost the same with "insert", but there is still a little difference
	public void meld(FibonacciHeap anotherHeap)
	{
		if(anotherHeap.minimumPointer == null)
			return;
		if(minimumPointer == null)
		{
			this.minimumPointer = anotherHeap.minimumPointer;
			return;
		}
		mergeTwoCircularLinkedList(minimumPointer, anotherHeap.minimumPointer);
		if(anotherHeap.minimumPointer.key < minimumPointer.key)
			minimumPointer = anotherHeap.minimumPointer;
		pairwiseCombine(minimumPointer); //we can also comment out this sentence
	}
	
	//caller of this function should be careful with situation when "minimumPointer" is null
	public TreeNode getMin()
	{ return minimumPointer; }
	
	public boolean isEmpty(){return minimumPointer == null;}
	
	//we must call "pairwiseCombine(...)" inside this "removeMin(...)" in order to achieve O(logn) amortized time complexity
	public boolean removeMin()
	{
		if(minimumPointer == null)
			return false;
			
		//be careful with situation when there is only one min tree in the Fibonacci heap (remember Fibonacci heap is collection of min trees)
		// so this means Fibonacci heap can have 1 min tree, or 2 min trees, or 3 min trees
		TreeNode next = minimumPointer.rightSibling;
		minimumPointer.rightSibling = null;
		if(next.rightSibling == null)//means only one min tree in the original Fibonacci heap
		{
			minimumPointer = minimumPointer.child;
			next = null;
			pairwiseCombine(minimumPointer);
			return true;
		}
		
		//otherwise there are more than one min tree in top level
		TreeNode child = minimumPointer.child;
		next.leftSibling = minimumPointer.leftSibling;
		minimumPointer.leftSibling.rightSibling = next;
		minimumPointer = next;

		//now we need to insert children into the top level
		if(child != null)
			mergeTwoCircularLinkedList(minimumPointer, child);

		//do pairwise combine
		pairwiseCombine(minimumPointer); //this "pairwiseCombine(...)" can not be commented out
		return true;
	}
	
	
	
	//this arbitrary remove accept an argument which is pointing to a existed node in the heap
	public boolean remove(TreeNode nodeInTheHeap) 
	{
		if(nodeInTheHeap == null) 
			return false;

		if(nodeInTheHeap.parent == null) //only node in the top level can have null parent
		{
			//we don't know whether "nodeInTheHeap" points to "minimum" node or not
			TreeNode next = nodeInTheHeap.rightSibling;
			nodeInTheHeap.rightSibling = null;
			if(next.rightSibling == null) //means only one min tree in the top level, and "nodeInTheHeap" is the "minimumPointer"
			{
				minimumPointer = minimumPointer.child;
				nodeInTheHeap = null;
				pairwiseCombine(minimumPointer);
			}
			else
			{
				TreeNode child = nodeInTheHeap.child;
				//first delete the "nodeInTheHeap" from the top level doubly circular linked list
				next.leftSibling = nodeInTheHeap.leftSibling;
				nodeInTheHeap.leftSibling.rightSibling = next;
				nodeInTheHeap = null;

				//be careful when "nodeInTheHeap" is the "minimumPointer"
				// so it's safe to set minimumPointer to an existed node
				minimumPointer = next;

				//now we need insert the child of "nodeInTheHeap" to the top level doubly circular linked list
				if(child != null)
					mergeTwoCircularLinkedList(minimumPointer, child);
					
				pairwiseCombine(minimumPointer);
			}
			return true;
		}
		else //otherwise "nodeInTheHeap" is not a top level node, then we must do cascading cut
		{
			TreeNode parent = nodeInTheHeap.parent;
			TreeNode child = nodeInTheHeap.child;

			//first try to put all children into the top level doubly circular linked list
			if(child != null)
				mergeTwoCircularLinkedList(minimumPointer, child);
			
			//now delete "nodeInTheHeap" from its own doubly circular linked list
			//be careful with when "nodeInTheHeap" is point by its parent
			TreeNode next = nodeInTheHeap.rightSibling;
			nodeInTheHeap.rightSibling = null;
			if(next.rightSibling == null) //means "nodeInTheHeap" is the only one node in its own doubly circular linked list
			{
				parent.child = null;
				parent.degree--;
				nodeInTheHeap = null;
			}
			else //in this case, "nodeInTheHeap" can either by pointed by its parent or not
			{
				if(parent.child.rightSibling == null) //"nodeInTheHeap" is pointed by its parent
				{
					next.leftSibling = nodeInTheHeap.leftSibling;
					nodeInTheHeap.leftSibling.rightSibling = next;
					parent.child = next;
					parent.degree--;
					nodeInTheHeap = null;
				}
				else //"nodeInTheHeap" isn't pointed by its parent
				{
					next.leftSibling = nodeInTheHeap.leftSibling;
					nodeInTheHeap.leftSibling.rightSibling = next;
					parent.degree--;
					nodeInTheHeap = null;
				}
			}
			
			//now do cascading cut
			TreeNode current = parent; 
			TreeNode last = cascadingCut(current);
			
			if(last != null && last.childCut == false && last.parent != null)
				last.childCut = true;
			
			pairwiseCombine(minimumPointer);
			return true;
		}
	}
	
	
	
	//"nodeInTheHeap" is a pointer which points to a current node in the heap, "_newKey" is the key we are going to assign to it
	public boolean decreaseKey(TreeNode nodeInTheHeap, int _newKey)
	{
		if(minimumPointer == null)
			return false;
		if(nodeInTheHeap == null)
			return false;
		if(nodeInTheHeap.key <= _newKey)
			return false;
			
		//now change the key
		nodeInTheHeap.key = _newKey;
		//only when nodeInTheHeap is not in top level doubly circular linked list and its
		// new key is smaller than its parent's, we would do something
		if(nodeInTheHeap.parent != null && _newKey < nodeInTheHeap.parent.key)
		{
			TreeNode current = nodeInTheHeap;
			TreeNode parent = current.parent;
			//we need to pull out current from its own doubly circular linked list and 
			// put it into top level doubly circular linked list
			extractAndInsert(current);
			//now we may need to do cascading cut if necessary
			current = parent; 
			TreeNode last = cascadingCut(current);
			
			if(last != null && last.childCut == false && last.parent != null)
				last.childCut = true;
			
			pairwiseCombine(minimumPointer);
		}
		return true;
	}
		
		
		
	//for below function, please draw figures to get the idea why I write as this.
	//parameter "first" and "second" are guaranteed not to be "null" (caller guaranteed), but for safety
	// I check it again inside the function.
	// Please be aware, both "first" and "second" are pointers to doubly circular linked list: a doubly circular linked
	// list could have one node or more nodes
	private void mergeTwoCircularLinkedList(TreeNode first, TreeNode second)
	{
		if(first == null || second == null) return;
		TreeNode rightSibling = first.rightSibling;
		TreeNode leftSibling = second.leftSibling;
		first.rightSibling = second;
		second.leftSibling = first;
		rightSibling.leftSibling = leftSibling;
		leftSibling.rightSibling = rightSibling;
	}
	
	
	
	//this private function pull out "current" from its own doubly circular linked list, and then insert "current" into 
	// top level doubly circular linked list. 
	// Please be aware, "current" can be only one single node or the root of a "min tree"
	void extractAndInsert(TreeNode current)
	{
		//if node's parent is already null, then means "node" already in the top level doubly circular linked list
		if(current == null || current.parent == null) return;
		
		TreeNode parent = current.parent;
		TreeNode next = current.rightSibling;
		//try to pull out "current" from its doubly circular linked list
		current.rightSibling = null;
		if(next.rightSibling == null) //"current" is the only node in its doubly circular linked list
		{
			parent.child = null;
			parent.degree--;
			current.leftSibling = current.rightSibling = current;
			mergeTwoCircularLinkedList(minimumPointer, current);
		}
		else //there are more than one nodes in current doubly circular linked list
		{
			//we should watch out whether "current" is pointed by "parent" or not
			if(parent.child.rightSibling == null) //pointed by parent, then we must change parent's child pointer
				parent.child = next;
			
			//first pull current out from its own doubly linked list
			next.leftSibling = current.leftSibling;
			current.leftSibling.rightSibling = next;

			parent.degree--;
			//then put current into top level doubly circular linked list
			current.leftSibling = current.rightSibling = current;
			mergeTwoCircularLinkedList(minimumPointer, current);
		}
	}
	
	
	
	//this private function is written to do cascading cut
	//param TreeNode current is the node we are going to do cascading cut
	//return TreeNode is the node which stop us
	// In fact "current" are guaranteed to have parent and have "childCut" as "true" (guaranteed by caller)
	// but I check this again inside the function.
	private TreeNode cascadingCut(TreeNode current)
	{
		//if current is null or top level node or haven't been dropping child before, we return
		if(current == null || current.parent == null || current.childCut == false)
			return current;
		
		TreeNode parent = null;
		while(current.parent != null && current.childCut == true)
		{
			parent = current.parent;
			extractAndInsert(current);
			current = parent;
		}
		return current;
	}
	
	

	//define pairwiseCombine as private function since this function only used by other functions
	// users shouldn't know this function is working.
	//This function would modify "minimumPointer" and "topLevelDegree"
	// in order to do pairwise combine, we need a "tree table" just as the slides indicate, we will use vector<TreeNode*> table as the table
	private void pairwiseCombine(TreeNode temporaryPointer)
	{
		//if the fibonacci heap is already empty, no need to do pairwise combine
		if(temporaryPointer == null) 
			return;
			
		ArrayList<TreeNode> table = new ArrayList<TreeNode>();
			
		//since our table's size is not guaranteed to be "maxDegree+1", so we set this "highestDegree" to 
		// help us save time when at last step we collect min trees from the table.
		//remember "maxDegree" is the max degree among all the top level min trees.
		int highestDegree = 0; 
		
		TreeNode current = temporaryPointer.rightSibling;
		temporaryPointer.rightSibling = null;
		
		while(current != null)
		{
			TreeNode next = current.rightSibling;

			current.rightSibling = current.leftSibling = current; //we immediately make the current min tree to a self-linked min tree
			current.parent = null;
			current.childCut = false;

			highestDegree = highestDegree > (current.degree) ? highestDegree: (current.degree);

			if(current.degree >= table.size()) // remember when size is "10", then the largest index is "9"
			{
				for(int size = table.size(); size <= current.degree; size++)
					table.add(null);
				table.set(current.degree, current);
			}
			else
			{
				int tempDegree = current.degree;
				if(table.get(tempDegree) == null)//There is no data in this entry
					table.set(tempDegree, current);
				else //otherwise we should combine as slide 12 page 18~19 shows, and during one round, we may need to do many combines
				{
					int count = 0;
					while(table.get(tempDegree) != null)
					{
						highestDegree = highestDegree > (tempDegree+1) ? highestDegree: (tempDegree+1);

						if(table.get(tempDegree).key < current.key)
						{
							if(table.get(tempDegree).child == null)
							{
								table.get(tempDegree).child = current;	
								current.parent = table.get(tempDegree);
							}
							else
							{
								TreeNode child = table.get(tempDegree).child;
								mergeTwoCircularLinkedList(child, current);
								current.parent = table.get(tempDegree);
							}
							(table.get(tempDegree).degree)++;
							current = table.get(tempDegree);
							table.set(tempDegree, null);
							tempDegree++;
							if(tempDegree >= table.size())
							{
								for(int size = table.size(); size <= tempDegree; size++)
									table.add(null);
							}
						}
						else
						{
							if(current.child == null)
							{
								current.child = table.get(tempDegree);
								table.get(tempDegree).parent = current;
							}
							else
							{
								TreeNode child = current.child;
								mergeTwoCircularLinkedList(child, table.get(tempDegree));
								table.get(tempDegree).parent = current;
							}
							(current.degree)++;
							table.set(tempDegree, null);
							tempDegree++;
							if(tempDegree >= table.size())
							{
								for(int size = table.size(); size <= tempDegree; size++)
									table.add(null);
							}
						}
						count++;
					}
					table.set(tempDegree, current);
				}
			}
			current = next;
		}
		
		//now we need to collect all entries in the table and reset the "minimumPointer"
		minimumPointer = null;
		for(int i = 0; i <= highestDegree; i++)
		{
			if(table.get(i) != null)
			{
				if(minimumPointer == null)
				{
					minimumPointer = table.get(i);
					minimumPointer.rightSibling = minimumPointer.leftSibling = minimumPointer;
				}
				else
				{
					//now insert new min tree to the top level doubly circular linked list
					TreeNode rightsibling = minimumPointer.rightSibling;
					minimumPointer.rightSibling = table.get(i);
					table.get(i).leftSibling = minimumPointer;
					table.get(i).rightSibling = rightsibling;
					rightsibling.leftSibling = table.get(i);
					if(table.get(i).key < minimumPointer.key)
						minimumPointer = table.get(i);
				}
			}
		}
	}
	

	private TreeNode minimumPointer;
}