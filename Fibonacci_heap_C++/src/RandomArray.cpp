#include <vector>
#include "RandomArray.h"
#include <limits.h>
using namespace std;

int RandomArray::searchMst(Graph &g)
{
	int vertices = g.getNumOfVertices();
	int edges = g.getNumOfEdges();
	vector<bool> visited(vertices, false);
	vector<int> distance(vertices, INT_MAX);
	
	vector<pair<int, int> > neighbors = g.getNeighbors(0);
	for(int i = 0; i < neighbors.size(); i++)
	{
		int v = neighbors[i].first;
		int cost = neighbors[i].second;
		distance[v] = cost; 
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
			if(visited[i] == false && distance[i] < minimumLength)
			{
				minimumLength = distance[i];
				index = i;
			}
		}
		
		visited[index] = true;
		count++;
		totalLength += minimumLength;
		
		neighbors = g.getNeighbors(index);
		for(int i = 0; i < neighbors.size(); i++)
		{
			int v = neighbors[i].first;
			int cost = neighbors[i].second;
			if(visited[v] == false && distance[v] > cost)
				distance[v] = cost;
		}
	}
		
	return totalLength;
}
