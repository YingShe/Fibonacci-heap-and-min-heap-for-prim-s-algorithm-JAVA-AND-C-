#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "Graph.h"
#include "RandomArray.h"
#include "RandomFiHeap.h"
#include "UserInputArray.h"
#include "UserInputFiHeap.h"
using namespace std;

void Usage()
{
	cout << "====================================================================================\n";
	cout << "you can run this program in two modes:\n";
	cout << "\t(i) random mode\n";
	cout << "\t\t./mst -r n d\n";
	cout << "\t(ii) user input mode\n";
	cout << "\t\t./mst -s file-name or\n";
	cout << "\t\t./mst -f file-name.\n";
	cout << "\'n\'and \'d\' must be positive integers, \'file-name\' must exist in your specified directory.\n";
	cout << "=====================================================================================\n";
	exit(1);
}

int main(int argc, char** argv)
{
	//I will handle four cases, 
	//(1)random graph for fibonacci heap implementation
	//(2)random graph for array implementation
	//(3)file input for fibonacci heap implementation
	//(4)file input for array implementation

	if(argc == 4)//means we will construct a random file
	{
		int vertices = atoi(argv[2]);
		int density = atoi(argv[3]); 
		int edges = vertices*(vertices-1)/2*density/100;

		if(vertices <= 0 || density <= 0 || density > 100 || edges < vertices-1)
			Usage();
		
		Graph g;
		while(g.isConnected() == false)
		{
			g.buildRandomGraph(vertices, edges);
			g.checkConnectedness();
		}
		int totalLengthHeap = 0, totalLengthArray = 0;

		clock_t Start, Time;
		Start = clock();
		RandomArray prim;
		int length1 = prim.searchMst(g);
		Time = clock() - Start;
		cout << "simple scheme length = " << length1 << ", clock ticks = " << Time << "; ";
		Start = clock();
		RandomFiHeap mst;
		int length2 = mst.searchMst(g);
		Time = clock() - Start;
		cout << "fi heap scheme length = " << length2 << ", clock ticks = " << Time << ".\n";
	}
	else if(argc == 3)
	{
		Graph g;
		g.buildGraphFromFile(argv[2]);
		if(g.checkConnectedness() == false)
		{
			cout << "The graph you select is non-connected, please try another graph!" << endl;
			Usage();
		}
		if(argv[1][1] == 's')
		{
			UserInputArray mst;
			mst.searchMst(g);
		}
		else if(argv[1][1] == 'f')
		{
			UserInputFiHeap mst;
			mst.searchMst(g);
		}
		else
			Usage();
	}
	else
		Usage();
	
	return 0;
}


