#ifndef _RANDOM_MIN_HEAP_H_
#define _RANDOM_MIN_HEAP_H_

#include "MinHeap.h"
#include "Graph.h"

class RandomMinHeap{
	public:
		RandomMinHeap(){}
		~RandomMinHeap(){}
	public:
		int searchMst(Graph &g);		
};

#endif
