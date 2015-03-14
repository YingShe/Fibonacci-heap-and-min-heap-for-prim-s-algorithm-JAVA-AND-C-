#include <vector>
#include <queue>
#include "UserInputMinHeap.h"
#include <iostream>
using namespace std;

int UserInputMinHeap::searchMst(Graph &g)
{
	vector<pair<int,int> > spanningTreeEdges;

	int vertices = g.getNumOfVertices();
	int edges = g.getNumOfEdges();
	
	vector<bool> visited(vertices, false);
	vector<TreeNode*> help(vertices);
	
	MinHeap mheap;
	vector<pair<int, int> > neighbors = g.getNeighbors(0);
	for(int i = 0; i < neighbors.size(); i++)
	{
		int destination = neighbors[i].first;
		int distance = neighbors[i].second;
		TreeNode *tmp = new TreeNode(distance, destination, 0);
		help[destination] = tmp;
		mheap.insert(tmp);
	}	
	

	visited[0] = true;
	int count = 1;
	int totalLength = 0;

	while(count < vertices)
	{
		TreeNode *mini = mheap.getMin();
		int length = mini->getKey();
		int identity = mini->getIdentity();

		pair<int, int> t(mini->getNeighbor(), mini->getIdentity());
		spanningTreeEdges.push_back(t);

		totalLength += length;
		visited[identity] = true;
		count++;

		mheap.removeMin();
	
		neighbors = g.getNeighbors(identity);
		for(int i = 0; i < neighbors.size(); i++)
		{
			int v = neighbors[i].first;
			int cost = neighbors[i].second;
			if(visited[v] == false)
			{
				if(help[v] == NULL)
				{
					TreeNode *tmp = new TreeNode(cost, v, identity);
					help[v] = tmp;
					mheap.insert(tmp);
				}
				else if(help[v]->getKey() > cost)
				{
					help[v]->setNeighbor(identity);
					mheap.decreaseKey(help[v], cost);
				}
			}
		}
	}	

	cout << totalLength << endl;
	for(int i = 0; i < spanningTreeEdges.size(); i++)
		cout << spanningTreeEdges[i].first << " " << spanningTreeEdges[i].second << endl;

	return totalLength;
}
