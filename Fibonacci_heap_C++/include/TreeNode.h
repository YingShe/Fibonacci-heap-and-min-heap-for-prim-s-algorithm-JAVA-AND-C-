#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

#include <stdlib.h> //I include <stdlib.h> here because "NULL" is declared in <stdlib.h> header file

//for this class, there is no need to provide another "TreeNode.cpp" file since all functions are defined inside class
class TreeNode{	
		//when declare friend function or class, no need to concern whether is "public" or "private"
		friend class FibonacciHeap; 
	public:
		TreeNode(){
			identity = -1;
			neighbor = -1;
			degree = 0;
			child = NULL;
			leftSibling = rightSibling = this;
			parent = NULL;
			childCut = false;	
		}
		//constructor
		TreeNode(int _data, int _identity):data(_data), identity(_identity){
			degree = 0;
			child = NULL;
			leftSibling = rightSibling = this;
			parent = NULL;
			childCut = false;
		}
		//overloaded constructor
		TreeNode(int _data, int _identity, int _neighbor):data(_data), identity(_identity), neighbor(_neighbor){
			degree = 0;
			child = NULL;
			leftSibling = rightSibling = this;
			parent = NULL;
			childCut = false;
		}
	public:
		///getter for "data". I define them inside the class since their logic is simple.
		int getData(){
			return data;
		}
		///setter for "data". I define them inside the class since their logic is simple.
		void setData(int _newData){
			data = _newData;
		}
		int getIdentity(){
			return identity;
		}
		void setIdentity(int _identity){
			identity = _identity;
		}
		int getNeighbor(){
			return neighbor;
		}
		void setNeighbor(int _neighbor){
			neighbor = _neighbor;
		}

	private:
		//these two member variables are not must for Fibonacci heap
		//but in order to use Fibonacci heap as the underlying data structure
		//for Prim's algorithm, we need these two variables
		int identity; ///the index of this vertex 
		int neighbor; ///the index of the vertex that connnect this vertex in MST

	private:
		int degree;
		TreeNode* child;
		TreeNode* leftSibling;
		TreeNode* rightSibling;
		TreeNode* parent;
		bool childCut;
		int data;
};


#endif
