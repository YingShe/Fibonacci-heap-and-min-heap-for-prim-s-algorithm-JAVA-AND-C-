package com.yingshe;

import com.yingshe.heap.factory.*;
import com.yingshe.heap.fiheap.*;
import com.yingshe.heap.minheap.*;
import com.yingshe.heap.*;
import com.yingshe.graph.*;
import java.util.*;
import java.lang.*;


public class MST{
	public static void main(String[] args)
	{
		HeapFactory factory = new HeapFactory();

		if(args.length == 3)
		{
			int vertices = Integer.valueOf(args[1]);
			int density = Integer.valueOf(args[2]);
			int edges = vertices*(vertices-1)/2*density/100;
			if(vertices <= 0 || density <= 0 || density > 100 || edges < vertices -1)
				Usage();
			
			Graph g = new Graph();
			while(g.isConnected() == false)
			{
				g.buildRandomGraph(vertices, edges);
				g.checkConnectedness();
			}
			IHeap heap = factory.getHeap("fibonacci");
			ArrayList<Edge> spanningTree = new ArrayList<Edge>();
			long start1 = System.currentTimeMillis();
			int len1 = searchMSTFromGraph(heap, g, spanningTree);
			long end1 = System.currentTimeMillis();
			heap = factory.getHeap("min");
			spanningTree.clear();
			long start2 = System.currentTimeMillis();
			int len2 = searchMSTFromGraph(heap, g, spanningTree);
			long end2 = System.currentTimeMillis();
			spanningTree.clear();
			long start3 = System.currentTimeMillis();
			int len3 = searchMSTFromGraph(g, spanningTree);
			long end3 = System.currentTimeMillis();	
			//System.out.println("Fibonacci heap length: "+ len1 + ";  min heap length: " + len2 + "; simple array length: " + len3 + ".");
			System.out.println("Fibonacci heap time: " + (end1-start1) + "; min heap time: " + (end2-start2) + "; simple array time: " + (end3-start3) + ".");
		}
		else if(args.length == 2)
		{
			Graph g = new Graph();
			g.buildGraphFromFile(args[1]);
			if(g.checkConnectedness()==false)
				Usage();
			ArrayList<Edge> spanningTree = new ArrayList<Edge>();
			int length = 0;
			if(args[0].equals("-s"))
				length = searchMSTFromGraph(g, spanningTree);
			else if(args[0].equals("-f"))	
				length = searchMSTFromGraph(factory.getHeap("fibonacci"), g, spanningTree);
			else if(args[0].equals("-m"))
				length = searchMSTFromGraph(factory.getHeap("min"), g, spanningTree);
			System.out.println("the spanning tree is " + length);
		}
		else
			Usage();
	}


	static int searchMSTFromGraph(IHeap heap, Graph g, ArrayList<Edge> spanningTree)
	{
		int vertices = g.getNumberOfVertices();
		int edges = g.getNumberOfEdges();
		
		boolean[] visited = new boolean[vertices];
		TreeNode[] help = new TreeNode[vertices];

		ArrayList<Edge> neighbors = g.getNeighbors(0);
		for(Edge e : neighbors)
		{
			int destination = e.destination;
			int distance = e.distance;
			TreeNode tmp = new TreeNode(distance, destination, 0);
			help[destination] = tmp;
			heap.insert(tmp);
		}	
		
		visited[0] = true;
		int count = 1;
		int totalLength = 0;
		while(count < vertices)
		{
			TreeNode mini = heap.getMin();
			int distance = mini.getKey();
			int destination = mini.getIdentity();

			Edge t = new Edge(mini.getNeighbor(), destination);
			spanningTree.add(t);
			
			totalLength += distance;
			visited[destination] = true;
			count++;

			heap.removeMin();

			neighbors = g.getNeighbors(destination);
			for(Edge e : neighbors)
			{
				int des = e.destination;
				int dis = e.distance;
				if(visited[des] == false)
				{
					if(help[des] == null)
					{
						TreeNode tmp = new TreeNode(dis, des, destination);
						help[des] = tmp;
						heap.insert(tmp);
					}
					else if(help[des].getKey() > dis)
					{
						help[des].setNeighbor(destination);
						heap.decreaseKey(help[des], dis);
					}
				}
			}
		}
		return totalLength;	
	}	

	static int searchMSTFromGraph(Graph g, ArrayList<Edge> spanningTree)
	{
		int vertices = g.getNumberOfVertices();
		int edges = g.getNumberOfEdges();
		
		boolean[] visited = new boolean[vertices];
		//arr[i][0] is the distance from other vertices to vertex i, 
		//arr[i][1] is the neighbor of vertex i
		int[][] arr = new int[vertices][2];
		for(int i = 0; i < vertices; i++)
			arr[i][1] = -1;

		ArrayList<Edge> neighbors = g.getNeighbors(0);
		for(Edge e : neighbors)
		{
			arr[e.destination][0] = e.distance;
			arr[e.destination][1] = 0;
		}		

		visited[0] = true;
		int count = 1;
		int totalLength = 0;
		while(count < vertices)
		{
			int minimumLength = Integer.MAX_VALUE;
			int index = -1;
			for(int i = 0; i < vertices; i++)
			{
				if(visited[i] == false && arr[i][1] != -1 && arr[i][0] < minimumLength)
				{
					minimumLength = arr[i][0];
					index = i;
				} 
			}
		
			Edge e = new Edge(arr[index][1], index);
			spanningTree.add(e);

			count++;
			totalLength += minimumLength;
			visited[index] = true;

			neighbors = g.getNeighbors(index);
			for(Edge e1 : neighbors)
			{
				int des = e1.destination;
				int dis = e1.distance;
				if(visited[des] == false && (arr[des][1]==-1 || arr[des][0] > dis))
				{
					arr[des][0] = dis;
					arr[des][1] = index;
				}
			}
		}
		return totalLength;
	}

	static void Usage()
	{
		System.out.println("=========================================================================================");
		System.out.println("you can run this program in two modes:");
		System.out.println("\t(i) random mode");
		System.out.println("\t\t java com/yingshe/MST -r n d");
		System.out.println("\t(ii) user input mode");
		System.out.println("\t\t java com/yingshe/MST -s file-name or");
		System.out.println("\t\t java com/yingshe/MST -f file-name or");
		System.out.println("\t\t java com/yingshe/MST -m file-name");
		System.out.println("-----------------------------------------------------------------------------------------");
		System.out.println("Above 'n' and 'd' must be positive integers, 'd' must between 1 and 100.");
		System.out.println("'-s' means use simple array, '-f' means use Fibonacci heap, '-m' means use min heap");
		System.out.println("=========================================================================================");
	}
}
