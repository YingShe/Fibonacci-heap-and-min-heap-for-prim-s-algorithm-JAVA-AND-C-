package com.yingshe.graph;

public class Edge{
	public int destination;
	public int distance;
	public Edge()
	{
		destination = distance = -1;
	}
	public Edge(int destination, int distance)
	{
		this.destination = destination;
		this.distance = distance;
	} 
}
