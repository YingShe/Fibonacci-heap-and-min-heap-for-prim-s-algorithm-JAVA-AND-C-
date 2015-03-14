package com.yingshe.graph;

import java.util.*;
import java.lang.Math;
import java.io.*;

public class Graph{
	private ArrayList<ArrayList<Edge>> udGraph;
	private boolean connected;
	private int numberOfVertices;
	private int numberOfEdges;

	public Graph()
	{
		numberOfVertices = numberOfEdges = 0;
		connected = false;
		udGraph = new ArrayList<ArrayList<Edge>>();
	}

	public Graph(Graph g)
	{
		numberOfVertices = g.numberOfVertices;
		numberOfEdges = g.numberOfEdges;
		connected = g.connected;
		udGraph = new ArrayList<ArrayList<Edge>>(g.udGraph);
	}

	public boolean isConnected(){return connected;}

	public boolean checkConnectedness()
	{
/*
		if(udGraph.size() == 0 || udGraph.size() != numberOfVertices)
		{connected = false; return false;}
		
		ArrayList<Boolean> con = new ArrayList<Boolean>();
		for(int i = 0; i < numberOfVertices; i++)
			con.add(false);

		con.set(0, true);
		int[] count = new int[1];
		count[0] = 1;

		dfs(0, con, count);
		connected = (count[0]==numberOfVertices?true:false);
*/
		connected = bfs();
		return connected;
	}

	public boolean buildRandomGraph(int vertices, int edges)
	{
		if(vertices <= 0 || edges < vertices-1 || edges > vertices*(vertices-1)/2)
			return false;	
		this.numberOfVertices = vertices;
		this.numberOfEdges = edges;
		this.udGraph = new ArrayList<ArrayList<Edge>>();
		for(int i = 0; i < numberOfVertices; i++)	
			this.udGraph.add(new ArrayList<Edge>());

		boolean[][] matrix = new boolean[vertices][vertices];

		int e = 0;
		while(e < edges)
		{
			//Math.random() generate real number in [0.0, 1.0)
			int v1 = (int)(Math.random()*vertices);
			int v2 = (int)(Math.random()*vertices);
			int distance = (int)(Math.random()*1000)+1;
			if(v1 != v2)
			{
				if(matrix[v1][v2] == false)
				{
					matrix[v1][v2] = matrix[v2][v1] = true;
					e++;
					Edge p1 = new Edge(v2, distance);
					udGraph.get(v1).add(p1);
					Edge p2 = new Edge(v1, distance);
					udGraph.get(v2).add(p2);
				}
			}
		}
		return true;
	}

	public boolean buildGraphFromFile(String filePath)
	{
		try{
			Scanner s = new Scanner(new File(filePath));
			if(s.hasNextInt()) numberOfVertices = s.nextInt();
			if(s.hasNextInt()) numberOfEdges = s.nextInt();
			if(numberOfVertices <= 0 || numberOfEdges < numberOfVertices -1)
				return false;
				
			udGraph = new ArrayList<ArrayList<Edge>> ();
			for(int i = 0; i < numberOfVertices; i++)
				udGraph.add(new ArrayList<Edge>());

			int e = 0;
			while(e < numberOfEdges)
			{
				int v1, v2, distance;
				v1 = s.nextInt();
				v2 = s.nextInt();
				distance = s.nextInt();
				Edge p1 = new Edge(v2, distance);
				udGraph.get(v1).add(p1);
				Edge p2 = new Edge(v1, distance);
				udGraph.get(v2).add(p2);
				e++;
			}
			s.close();
		}
		catch(Exception e)
		{
			System.out.println("In class Graph, function buildGraphFromFile, error in opening file: " + filePath);
		}
		return true;
	}


	public ArrayList<Edge> getNeighbors(int index)
	{
		if(index >= numberOfVertices) return null;
		return udGraph.get(index);
	}

	public int getNumberOfVertices()
	{ return numberOfVertices; }

	public void setNumberOfVertices(int vertices)
	{ numberOfVertices = vertices; }

	public int getNumberOfEdges()
	{ return numberOfEdges; }

	public void setNumberOfEdges(int edges)
	{ numberOfEdges = edges; }

	private void dfs(int index, ArrayList<Boolean> con, int[] count)
	{
		if(count[0] == numberOfVertices) return;
		for(int i = 0; i < udGraph.get(index).size(); i++)
		{
			int destination = udGraph.get(index).get(i).destination;
			if(con.get(destination) == false)
			{
				con.set(destination, true);
				count[0]++;
				dfs(destination, con, count);
			}
		}
	}

	private boolean bfs()
	{
		boolean[] visited = new boolean[numberOfVertices];
		Queue<Integer> tool = new LinkedList<Integer>();
		int i = 0;
		while(i < numberOfVertices && udGraph.get(i).size() == 0)
			i++;	

		tool.offer(i);
		visited[i] = true;
		int count = 1;

		while(!tool.isEmpty())
		{
			int tmp = tool.poll();
			ArrayList<Edge> neighbors = udGraph.get(tmp);
			for(Edge e : neighbors)
			{
				if(visited[e.destination] == false)
				{
					tool.offer(e.destination);
					visited[e.destination] = true;
					count++;
				}
			}
		}		
		return count==numberOfVertices;
	}
}
