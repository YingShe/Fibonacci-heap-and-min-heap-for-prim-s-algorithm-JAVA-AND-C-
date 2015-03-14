#ifndef _RANDOM_FI_HEAP_H_
#define _RANDOM_FI_HEAP_H_

#include "FibonacciHeap.h"
#include "Graph.h"

class RandomFiHeap{
	public:
		RandomFiHeap(){}
		~RandomFiHeap(){}
	public:
		int searchMst(Graph &g);		
};

#endif
