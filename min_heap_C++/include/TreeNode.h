#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

//I include <stdlib.h> since "NULL" is declared in this old C header file
#include <stdlib.h>

class TreeNode{
	friend class MinHeap; //
	public:
		//default constructor. The definition(definition always include declaration) is inside the class since logic is simple
		TreeNode(){
			leftChild = rightChild = parent = NULL; //by default, we set "leftChild" and "rightChild" to NULL
			numInLeftSubtree = 0;
			numInRightSubtree = 0;
		}
		//another overloaded constructor. The definition(definition always include declaration) is inside the class since logic is simple
		TreeNode(int _key, int _identity){
			key = _key;
			identity = _identity;
			leftChild = rightChild = parent = NULL;
			numInLeftSubtree = 0;
			numInRightSubtree = 0;
		}
		//overloaded constructor
		TreeNode(int _key, int _identity, int _neighbor):key(_key), identity(_identity), neighbor(_neighbor){
			leftChild = rightChild = parent = NULL;
			numInLeftSubtree = 0;
			numInRightSubtree = 0;
		}
		//destructor, we don't have anything to do so provide a empty brace
		~TreeNode(){}
		
	public:
		///getter for "data". I define them inside the class since their logic is simple.
		int getKey(){
			return key;
		}
		///setter for "data". I define them inside the class since their logic is simple.
		void setKey(int _newKey){
			key = _newKey;
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
		//in our implementation, the number of nodes in the left sub tree of this
		//node is "x", and the number of nodes in the right sub tree of this node is "y", our goal is to keep 
		//"x" roughly equal to "y", better to keep the equation "abs(x-y) <= 1"
		//this property is added for our Prim's implementation
	private:
		int numInLeftSubtree;
		int numInRightSubtree;
		
		int key; 				//you can also use "int value" or "int data"
		int identity;
		int neighbor; ///the index of the vertex that connnect this vertex in MST
		TreeNode* leftChild; 	//pointer points to the left child, default to "NULL"
		TreeNode* rightChild; 	//pointer points to the right child, default to "NULL"
		TreeNode* parent;
};
#endif
