#include <vector>
#include <queue>
#include "RandomFiHeap.h"
using namespace std;

int RandomFiHeap::searchMst(Graph &g)
{
	int vertices = g.getNumOfVertices();
	int edges = g.getNumOfEdges();
	
	vector<bool> visited(vertices, false);
	vector<TreeNode*> help(vertices);
	
	FibonacciHeap fheap;
	vector<pair<int, int> > neighbors = g.getNeighbors(0);
	for(int i = 0; i < neighbors.size(); i++)
	{
		int identity = neighbors[i].first;
		int data = neighbors[i].second;
		TreeNode *tmp = new TreeNode(data, identity);
		help[identity] = tmp;
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
					TreeNode *tmp = new TreeNode(cost, v);
					help[v] = tmp;
					fheap.insert(tmp);
				}
				else if(help[v]->getData() > cost)
					fheap.decreaseKey(help[v], cost);
			}
		}
	}	
	return totalLength;
}
