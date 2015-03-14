#ifndef _FIBONACCI_HEAP_H_
#define _FIBONACCI_HEAP_H_

#include "TreeNode.h"
#include <vector> //we include this header file since "pairwiseCombine" would use vector
using namespace std;


//as we know, fibonacci heap is similar with fibonacci heap, the action fibonacci provide is
//(1) Insert (either insert a single node or a min tree)
//(2) RemoveMin
//(3) Meld (meld with another fibonacci heap, since a fibonacci heap is a collection of min trees, so a fibonacci heap can be a single min tree
//			or, even a single node, so "Meld" is much similar with "Insert")
//(4) Remove (this function can also perform "removeMin")
//(5) DecreaseKey
// For our implementation, we would provide "pairwiseCombine"
class FibonacciHeap{
	public:
		//default constructor
		FibonacciHeap(){
			minimumPointer = NULL;
		}
		//another overloaded constructor
		FibonacciHeap(TreeNode* _minimumPointer):minimumPointer(_minimumPointer){}
		
	public:
		//anotherTree could be only one single node tree, or be a "min tree"
		//after insert, we will call "pariwiseCombine(...)", and in fact, we can also not call "pairwiseCombine(...)" in this "insert(...)"
		// If we call, the time complexity for "insert(...)" is not O(1), but O(logn)
		void insert(TreeNode* anotherTree);
		//anotherHeap is another fibonacci heap, we will change "anotherHeap", so we use reference
		//after meld, we will call "pairwiseCombine(...)"
		// to be honest, this "meld" function is much the same with "insert", but there is a little difference
		void meld(FibonacciHeap& anotherHeap);
		TreeNode* getMin(); //this function is added by myself to utilize fibonacci heap
		//we must call "pairwiseCombine(...)" inside this "removeMin(...)" in order to achieve O(logn) amortized time complexity
		bool removeMin();
		bool remove(TreeNode*& nodeInTheHeap); //this arbitrary remove accept an argument which is pointing to a existed node in the heap
		//"nodeInTheHeap" is a pointer which points to a current node in the heap, "_newKey" is the key we are going to assign to it
		bool decreaseKey(TreeNode* nodeInTheHeap, int _newKey); 

	private:
		//this function merge two doubly circular linked lists together
		void mergeTwoCircularLinkedList(TreeNode* first, TreeNode* second);
		//this function extract "current" from its own doubly circular linked list and insert it into top level
		//doubly linked list
		void extractAndInsert(TreeNode* current);
		//this function do cascading cut, "current" is a node who lost its child just now
		//return a node who is "current" ancestor and who haven't lost child before
		TreeNode* cascadingCut(TreeNode* current);
		//define pairwiseCombine as private function since this function only used by other functions
		// users shouldn't know this function is working.
		//This function would modify "minimumPointer" and "topLevelDegree"
		// in order to do pairwise combine, we need a "tree table" just as the slides indicate, we will use vector<TreeNode*> table as the table
		void pairwiseCombine(TreeNode *temporayPointer); 
	private:
		TreeNode* minimumPointer;
};

#endif
