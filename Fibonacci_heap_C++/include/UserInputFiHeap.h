#ifndef _USER_INPUT_FI_HEAP_H_
#define _USER_INPUT_FI_HEAP_H_

#include "Graph.h"
#include "FibonacciHeap.h"

class UserInputFiHeap{
	public:
		UserInputFiHeap(){}
		~UserInputFiHeap(){}
	public:
		int searchMst(Graph &g);		
};

#endif
