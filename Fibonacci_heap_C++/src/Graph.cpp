#include "Graph.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

bool Graph::isConnected()
{
	return connected;
}

bool Graph::checkConnectedness()
{
	if(udGraph.size() == 0)
		return false;
	if(udGraph.size() != numberOfVertices)
		return false;

	vector<bool> con(numberOfVertices, false);
	con[0] = true;
	int count = 1;
	dfs(0, con, count);
	connected = (count==numberOfVertices?true:false);
	return connected;	
}

void Graph::dfs(int index, vector<bool> &con, int &count)
{
	for(int i = 0; i < udGraph[index].size(); i++)
	{
		int neighbor = udGraph[index][i].first;
		if(con[neighbor] == false)
		{
			con[neighbor] = true;
			count++;
			dfs(neighbor, con, count);
		}
	}
}

bool Graph::buildRandomGraph(int vertices, int edges)
{
	if(vertices <= 0 || edges < vertices-1 || edges > vertices*(vertices-1)/2)
		return false;

	this->numberOfVertices = vertices;
	this->numberOfEdges = edges;
	this->udGraph = vector<vector<pair<int, int> > > (vertices);
	
	vector<vector<bool> > matrix(vertices, vector<bool>(vertices, false));

	//get a seed according to system time
	srand((unsigned int)time(0));

	int e = 0;
	while(e < edges)
	{
		int v1 = rand()%vertices;
		int v2 = rand()%vertices;
		int cost = rand()%1000 + 1;
		if(v1 != v2)
		{
			if(matrix[v1][v2] == false)
			{
				matrix[v1][v2] = matrix[v2][v1] = true;
				e++;
				pair<int, int> p1(v2, cost);
				udGraph[v1].push_back(p1);
				pair<int, int> p2(v1, cost);
				udGraph[v2].push_back(p2);
			}			
		}
	}
	return true;
}


bool Graph::buildGraphFromFile(char* filePath)
{
	ifstream infile(filePath);
	if(infile.is_open() == false)
		return false;

	int vertices, edges;
	infile >> vertices >> edges;
	if(vertices <= 0 || edges < vertices-1)
		return false;

	numberOfVertices = vertices;
	numberOfEdges = edges;
	udGraph = vector<vector<pair<int,int> > > (vertices);


	int e  = 0;
	while(e < edges)
	{
		int v1, v2, cost;
		infile >> v1 >> v2 >> cost;
		pair<int, int> p1(v2, cost);
		udGraph[v1].push_back(p1);
		pair<int, int> p2(v1, cost);
		udGraph[v2].push_back(p2);
		e++;
	}
	infile.close();
	return true;
}

vector<pair<int, int> > Graph::getNeighbors(int index)
{
	if(index >= numberOfVertices)
		return vector<pair<int,int> >();
	return udGraph[index];
}

int Graph::getNumOfVertices()
{
	return numberOfVertices;
}

void Graph::setNumOfVertices(int _vertices)
{
	numberOfVertices = _vertices;
}

int Graph::getNumOfEdges()
{
	return numberOfEdges;
}

void Graph::setNumOfEdges(int _edges)
{
	numberOfEdges = _edges;
}
