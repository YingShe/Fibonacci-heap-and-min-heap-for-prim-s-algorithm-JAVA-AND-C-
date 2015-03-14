#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>

class Graph{
	public :
		Graph(){
			numberOfVertices = 0;
			numberOfEdges = 0;
			connected = false;
		}
		Graph(const Graph &g){
			numberOfVertices = g.numberOfVertices;
			numberOfEdges = g.numberOfEdges;
			connected = g.connected;
			udGraph = g.udGraph;
		}
		~Graph(){}

	public:
		bool isConnected();
		bool checkConnectedness();
		bool buildRandomGraph(int vertices, int edges);
		bool buildGraphFromFile(char *filePath);
		std::vector<std::pair<int,int> > getNeighbors(int index);
	public:
		int getNumOfVertices();
		void setNumOfVertices(int _vertices);
		int getNumOfEdges();
		void setNumOfEdges(int _edges);
	
	public:
		void showGraph();
	private:	
		void dfs(int index, std::vector<bool> &con, int &count);

	private:
		//the underlying graph representation
		std::vector<std::vector<std::pair<int, int> > > udGraph;
		bool connected;
		int numberOfVertices;
		int numberOfEdges;
};

#endif
