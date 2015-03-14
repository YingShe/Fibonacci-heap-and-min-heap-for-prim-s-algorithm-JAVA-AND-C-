#include <vector>
#include <iostream>
#include "UserInputArray.h"
#include <limits.h>
using namespace std;

int UserInputArray::searchMst(Graph &g)
{
	vector<pair<int, int> > spanningTreeEdges;

	int vertices = g.getNumOfVertices();
	int edges = g.getNumOfEdges();
	vector<bool> visited(vertices, false);
	vector<pair<int, int> > distance(vertices, pair<int, int>(INT_MAX, -1));
	
	vector<pair<int, int> > neighbors = g.getNeighbors(0);
	for(int i = 0; i < neighbors.size(); i++)
	{
		int v = neighbors[i].first;
		int cost = neighbors[i].second;
		distance[v].first = cost;
		distance[v].second = 0;
	}

	visited[0] = true;
	int count = 1;
	int totalLength = 0;

	while(count < vertices)
	{
		int minimumLength = INT_MAX;
		int index = -1;
		for(int i = 0; i < vertices; i++)
		{
			if(visited[i] == false && distance[i].first < minimumLength)
			{
				minimumLength = distance[i].first;
				index = i;
			}
		}

		pair<int, int> t(distance[index].second, index);
		spanningTreeEdges.push_back(t);

		count++;
		totalLength += minimumLength;
		visited[index] = true;

		neighbors = g.getNeighbors(index);
		for(int i = 0; i < neighbors.size(); i++)
		{
			int v = neighbors[i].first;
			int cost = neighbors[i].second;
			if(visited[v] == false && distance[v].first > cost)
			{
				distance[v].first = cost;
				distance[v].second = index;
			}
		}
	}

	cout << totalLength << endl;
	for(int i = 0; i < spanningTreeEdges.size(); i++)
		cout << spanningTreeEdges[i].first << " " << spanningTreeEdges[i].second << endl;
	return totalLength;
}
