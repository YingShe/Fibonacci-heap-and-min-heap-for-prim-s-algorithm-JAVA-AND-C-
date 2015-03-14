#ifndef _USER_INPUT_MIN_HEAP_H_
#define _USER_INPUT_MIN_HEAP_H_

#include "MinHeap.h"
#include "Graph.h"

class UserInputMinHeap{
	public:
		UserInputMinHeap(){}
		~UserInputMinHeap(){}
	public:
		int searchMst(Graph &g);		
};

#endif
