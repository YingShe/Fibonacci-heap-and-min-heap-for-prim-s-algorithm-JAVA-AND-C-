#include "FibonacciHeap.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

//anotherTree could be only one single node tree, or be a "min tree"
//after insert, we will call "pariwiseCombine(...)", and in fact, we can also not call "pairwiseCombine(...)" in this "insert(...)"
// If we call, the actual time complexity for "insert(...)" is not O(1), but O(logn). But pairwise combine make 
// other function less amortized time complexity
void FibonacciHeap::insert(TreeNode* anotherTree)
{
	anotherTree->parent = NULL;
	anotherTree->childCut = false;
	
	if(minimumPointer == NULL) //if the original fibonacci heap is empty
	{
		minimumPointer = anotherTree;
		return;
	}
	
	mergeTwoCircularLinkedList(minimumPointer, anotherTree);
	//now need to reset the minimum pointer if necessary
	if(anotherTree->data < minimumPointer->data)
		minimumPointer = anotherTree;
	
	//even actual time complexity for inserting is O(1), but we still call "pairwiseCombine(...)". we can comment 
	// this statement out and achieve the same time complexity. But I include it here for personal preference
	pairwiseCombine(minimumPointer);
}


//anotherHeap is another Fibonacci heap (remember, a min Fibonacci heap is a collection of min tree)
//after meld, we will call "pairwiseCombine(...)"
// to be honest, this "meld" function is almost the same with "insert", but there is still a little difference
void FibonacciHeap::meld(FibonacciHeap& anotherHeap)
{
	if(anotherHeap.minimumPointer == NULL)
		return;
		
	if(minimumPointer == NULL)
	{
		*(this) = anotherHeap;
		return;
	}
	mergeTwoCircularLinkedList(minimumPointer, anotherHeap.minimumPointer);
	if(anotherHeap.minimumPointer->data < minimumPointer->data)
		minimumPointer = anotherHeap.minimumPointer;
	
	pairwiseCombine(minimumPointer); //we can also comment out this sentence
}
		
		
TreeNode* FibonacciHeap::getMin()
{
	return minimumPointer; //caller of this function should be careful with situation when "minimumPointer" is NULL
}


bool FibonacciHeap::removeMin()
{

	if(minimumPointer == NULL)
		return false;
		
	//be careful with situation when there is only one min tree in the fibonacci heap (remember fibonacci heap is collection of min trees)
	TreeNode* next = minimumPointer->rightSibling;
	minimumPointer->rightSibling = NULL;
	if(next->rightSibling == NULL)//means only one min tree in the original fibonacci heap
	{
		minimumPointer = minimumPointer->child;
		delete next;
		next = NULL;
		pairwiseCombine(minimumPointer);
		return true;
	}
	
	//otherwise there are more than one min tree in top level
	TreeNode* child = minimumPointer->child;
	next->leftSibling = minimumPointer->leftSibling;
	minimumPointer->leftSibling->rightSibling = next;
	delete minimumPointer;
	minimumPointer = next;


	//now we need to insert children into the top level
	if(child != NULL)
		mergeTwoCircularLinkedList(minimumPointer, child);

	//do pairwise combine
	pairwiseCombine(minimumPointer); //this "pairwiseCombine(...)" can not be commented out
	return true;
}

//pairwiseCombine called in this function can not be commented out
bool FibonacciHeap::remove(TreeNode*& nodeInTheHeap)
{
	if(nodeInTheHeap == NULL) 
		return false;

	if(nodeInTheHeap->parent == NULL) //only node in the top level can have NULL parent
	{
		//we don't know whether "nodeInTheHeap" points to "minimum" node or not
		TreeNode* next = nodeInTheHeap->rightSibling;
		nodeInTheHeap->rightSibling = NULL;
		if(next->rightSibling == NULL) //means only one min tree in the top level, and "nodeInTheHeap" is the "minimumPointer"
		{
			minimumPointer = minimumPointer->child;
			delete nodeInTheHeap;
			nodeInTheHeap = NULL;
			pairwiseCombine(minimumPointer);
		}
		else
		{
			TreeNode* child = nodeInTheHeap->child;
			//first delete the "nodeInTheHeap" from the top level doubly circular linked list
			next->leftSibling = nodeInTheHeap->leftSibling;
			nodeInTheHeap->leftSibling->rightSibling = next;
			delete nodeInTheHeap;
			nodeInTheHeap = NULL;

			//be careful when "nodeInTheHeap" is the "minimumPointer"
			// so it's safe to set minimumPointer to an existed node
			minimumPointer = next;

			//now we need insert the child of "nodeInTheHeap" to the top level doubly circular linked list
			if(child != NULL)
				mergeTwoCircularLinkedList(minimumPointer, child);
				
			pairwiseCombine(minimumPointer);
		}
		return true;
	}
	else //otherwise "nodeInTheHeap" is not a top level node, then we must do cascading cut
	{
		TreeNode* parent = nodeInTheHeap->parent;
		TreeNode* child = nodeInTheHeap->child;

		//first try to put all children into the top level doubly circular linked list
		if(child != NULL)
			mergeTwoCircularLinkedList(minimumPointer, child);
		
		//now delete "nodeInTheHeap" from its own doubly circular linked list
		//be careful with when "nodeInTheHeap" is point by its parent
		TreeNode* next = nodeInTheHeap->rightSibling;
		nodeInTheHeap->rightSibling = NULL;
		if(next->rightSibling == NULL) //means "nodeInTheHeap" is the only one node in its own doubly circular linked list
		{
			parent->child = NULL;
			parent->degree--;
			delete nodeInTheHeap;
			nodeInTheHeap = NULL;
		}
		else //in this case, "nodeInTheHeap" can either by pointed by its parent or not
		{
			if(parent->child->rightSibling == NULL) //"nodeInTheHeap" is pointed by its parent
			{
				next->leftSibling = nodeInTheHeap->leftSibling;
				nodeInTheHeap->leftSibling->rightSibling = next;
				parent->child = next;
				parent->degree--;
				delete nodeInTheHeap;
				nodeInTheHeap = NULL;
			}
			else //"nodeInTheHeap" isn't pointed by its parent
			{
				next->leftSibling = nodeInTheHeap->leftSibling;
				nodeInTheHeap->leftSibling->rightSibling = next;
				parent->degree--;
				delete nodeInTheHeap;
				nodeInTheHeap = NULL;
			}
		}
		
		//now do cascading cut
		TreeNode* current = parent; 
		TreeNode* last = cascadingCut(current);
		
		if(last != NULL && last->childCut == false && last->parent != NULL)
			last->childCut = true;
		
		pairwiseCombine(minimumPointer);
		return true;
	}
}


//"nodeInTheHeap" is a pointer which points to a current node in the heap, "_newKey" is the key we are going to assign to it
bool FibonacciHeap::decreaseKey(TreeNode* nodeInTheHeap, int _newKey)
{
	if(minimumPointer == NULL)
		return false;
	if(nodeInTheHeap == NULL)
		return false;
	if(nodeInTheHeap->data <= _newKey)
		return false;
		
	//now change the key
	nodeInTheHeap->data = _newKey;
	//only when nodeInTheHeap is not in top level doubly circular linked list and its
	// new key is smaller than its parent's, we would do something
	if(nodeInTheHeap->parent != NULL && _newKey < nodeInTheHeap->parent->data)
	{
		TreeNode* current = nodeInTheHeap;
		TreeNode* parent = current->parent;
		extractAndInsert(current);
		//now we may need to do cascading cut
		current = parent; 
		TreeNode* last = cascadingCut(current);
		
		if(last != NULL && last->childCut == false && last->parent != NULL)
			last->childCut = true;
		
		pairwiseCombine(minimumPointer);
	}
}

//for below function, please draw figures to get the idea why I write as this.
//parameter "first" and "second" are guaranteed not to be "NULL" (caller guaranteed), but for safety
// I check it again inside the function.
// Please be aware, both "first" and "second" are pointers to doubly circular linked list: a doubly circular linked
// list could have one node or more nodes
void FibonacciHeap::mergeTwoCircularLinkedList(TreeNode* first, TreeNode* second)
{
	if(first == NULL || second == NULL) return;
	TreeNode* rightSibling = first->rightSibling;
	TreeNode* leftSibling = second->leftSibling;
	first->rightSibling = second;
	second->leftSibling = first;
	rightSibling->leftSibling = leftSibling;
	leftSibling->rightSibling = rightSibling;
}
	
	
	
//this private function pull out "current" from its own doubly circular linked list, and then insert "current" into 
// top level doubly circular linked list. 
// Please be aware, "current" can be only one single node or the root of a "min tree"
void FibonacciHeap::extractAndInsert(TreeNode* current)
{
	//if node's parent is already NULL, then means "node" already in the top level doubly circular linked list
	if(current == NULL || current->parent == NULL) return;
		
	TreeNode* parent = current->parent;
	TreeNode* next = current->rightSibling;
	//try to pull out "current" from its doubly circular linked list
	current->rightSibling = NULL;
	if(next->rightSibling == NULL) //"current" is the only node in its doubly circular linked list
	{
		parent->child = NULL;
		parent->degree--;
		current->leftSibling = current->rightSibling = current;
		mergeTwoCircularLinkedList(minimumPointer, current);
	}
	else //there are more than one nodes in current doubly circular linked list
	{
		//we should watch out whether "current" is pointed by "parent" or not
		if(parent->child->rightSibling == NULL) //pointed by parent, then we must change parent's child pointer
			parent->child = next;
			
		//first pull current out from its own doubly linked list
		next->leftSibling = current->leftSibling;
		current->leftSibling->rightSibling = next;

		parent->degree--;
		//then put current into top level doubly circular linked list
		current->leftSibling = current->rightSibling = current;
		mergeTwoCircularLinkedList(minimumPointer, current);
	}
}
	
	
	
//this private function is written to do cascading cut
//param TreeNode current is the node we are going to do cascading cut
//return TreeNode is the node which stop us
// In fact "current" are guaranteed to have parent and have "childCut" as "true" (guaranteed by caller)
// but I check this again inside the function.
TreeNode* FibonacciHeap::cascadingCut(TreeNode* current)
{
	//if current is NULL or top level node or haven't been dropping child before, we return
	if(current == NULL || current->parent == NULL || current->childCut == false)
		return current;
		
	TreeNode* parent = NULL;
	while(current->parent != NULL&& current->childCut == true)
	{
		parent = current->parent;
		extractAndInsert(current);
		current = parent;
	}
	return current;
}

		
void FibonacciHeap::pairwiseCombine(TreeNode *temporaryPointer)
{
	//if the fibonacci heap is already empty, no need to do pairwise combine
	if(temporaryPointer == NULL) 
		return;
		
	vector<TreeNode*> table(10); //we give the table 10 capacity for saving computation time, all entries would set to NULL
	
	//since our table's size is not "maxDegree+1", so we set this "highestDegree" to 
	// help us save time when at last we collect min trees from the table.
	int highestDegree = 0; 
	
	//remember "maxDegree" is the max degree among all the top level min trees.
	TreeNode *current = temporaryPointer->rightSibling;
	temporaryPointer->rightSibling = NULL;
	
	while(current != NULL)
	{
		TreeNode* next = current->rightSibling;

		current->rightSibling = current->leftSibling = current; //we immediately make the current min tree to a self-linked min tree
		current->parent = NULL;
		current->childCut = false;

		highestDegree = highestDegree > (current->degree) ? highestDegree: (current->degree);

		if(current->degree >= table.capacity()) // remember when capacity is "10", then the largest index is "9"
		{
			table.resize(table.capacity()*2); //of course you can times 3, times 4, times 5,..., but I think doubled it is better
			table[current->degree] = current;
		}
		else
		{
			int tempDegree = current->degree;
			if(table[tempDegree] == NULL)//There is no data in this entry
			{
				table[tempDegree] = current;
			}
			else //otherwise we should combine as slide 12 page 18~19 shows, and during one round, we may need to many combine
			{
				int count = 0;
				while(table[tempDegree] != NULL)
				{

					highestDegree = highestDegree > (tempDegree+1) ? highestDegree: (tempDegree+1);

					if(table[tempDegree]->data < current->data)
					{
						if(table[tempDegree]->child == NULL)
						{
							table[tempDegree]->child = current;	
							current->parent = table[tempDegree];
						}
						else
						{
							TreeNode* child = table[tempDegree]->child;
							mergeTwoCircularLinkedList(child, current);
							current->parent = table[tempDegree];
						}
						(table[tempDegree]->degree)++;
						current = table[tempDegree];
						table[tempDegree] = NULL;
						tempDegree++;
						if(tempDegree >= table.capacity())
							table.resize(tempDegree*2); //for safety, we need to check
					}
					else
					{
						if(current->child == NULL)
						{
							current->child = table[tempDegree];
							table[tempDegree]->parent = current;
						}
						else
						{
							TreeNode* child = current->child;
							mergeTwoCircularLinkedList(child, table[tempDegree]);
							table[tempDegree]->parent = current;
						}
						(current->degree)++;
						table[tempDegree] = NULL;
						tempDegree++;
						if(tempDegree >= table.capacity())
							table.resize(tempDegree*2); //for safety, we need to check
					}
					count++;
				}
				table[tempDegree] = current;
			}
		}
		current = next;
	}
	
	//now we need to collect all entries in the table and reset the "minimumPointer"
	minimumPointer = NULL;
	for(int i = 0; i <= highestDegree; i++)
	{
		if(table[i] != NULL)
		{
			if(minimumPointer == NULL)
			{
				minimumPointer = table[i];
				minimumPointer->rightSibling = minimumPointer->leftSibling = minimumPointer;
			}
			else
			{
				//now insert new min tree to the top level doubly circular linked list
				TreeNode* rightsibling = minimumPointer->rightSibling;
				minimumPointer->rightSibling = table[i];
				table[i]->leftSibling = minimumPointer;
				table[i]->rightSibling = rightsibling;
				rightsibling->leftSibling = table[i];
				if(table[i]->data < minimumPointer->data)
					minimumPointer = table[i];
			}
		}
	}
}












