package com.yingshe.heap.factory;

import com.yingshe.heap.*;
import com.yingshe.heap.fiheap.*;
import com.yingshe.heap.minheap.*;

public class HeapFactory{
	public IHeap getHeap(String type)
	{
		//default return Fibonacci heap
		if(type == null) return new FibonacciHeap();
		else if(type.equalsIgnoreCase("Fibonacci"))
			return new FibonacciHeap();
		else if(type.equalsIgnoreCase("min"))
			return new MinHeap();
		else
			return new FibonacciHeap();
	}
}
