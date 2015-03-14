#include <vector>
#include "FibonacciHeap.h"
#include "UserInputFiHeap.h"
#include <iostream>
using namespace std;

int UserInputFiHeap::searchMst(Graph &g)
{
	vector<pair<int,int> > spanningTreeEdges;

	int vertices = g.getNumOfVertices();
	int edges = g.getNumOfEdges();
	
	vector<bool> visited(vertices, false);
	vector<TreeNode*> help(vertices);
	
	FibonacciHeap fheap;
	vector<pair<int, int> > neighbors = g.getNeighbors(0);
	for(int i = 0; i < neighbors.size(); i++)
	{
		int v = neighbors[i].first;
		int cost = neighbors[i].second;
		TreeNode *tmp = new TreeNode(cost, v, 0);
		help[v] = tmp;
		fheap.insert(tmp);
	}		

	visited[0] = true;
	int count = 1;
	int totalLength = 0;

	while(count < vertices)
	{
		TreeNode *mini = fheap.getMin();
		int length = mini->getData();
		int identity = mini->getIdentity();

		pair<int, int> t(mini->getNeighbor(), mini->getIdentity());
		spanningTreeEdges.push_back(t);

		totalLength += length;
		visited[identity] = true;
		count++;

		fheap.removeMin();

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
					fheap.insert(tmp);
				}
				else if(help[v]->getData() > cost)
				{
					help[v]->setNeighbor(identity);
					fheap.decreaseKey(help[v], cost);
				}
			}
		}
	}	

	cout << totalLength << endl;
	for(int i = 0; i < spanningTreeEdges.size(); i++)
		cout << spanningTreeEdges[i].first << " " << spanningTreeEdges[i].second << endl;

	return totalLength;
}


