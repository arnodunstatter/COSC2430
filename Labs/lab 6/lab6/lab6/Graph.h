#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Vertex
{
	friend class Graph;

	int Number;
	//vector<bool> connections;
	//vector<int> distances;
	vector<pair<bool, int>> adjacency;
	Vertex(int, int);
	int numberOfConnections();
};


class Graph
{
	int vertices, edges, start, end;
	vector<Vertex*> graph;
	
	
	int dijkstra(); //makes a vector called distancesFromStart and returns distance from start to end
	bool dijkstraNotDone(vector<pair<int, int>> connections); //checks if all edges have been checked
	int indexOfClosestUncheckedVertex(const vector<pair<bool, int>> currentAdjacencyVector, const vector<pair<int, int>> connections); //returns index of closest vertex

public:
	Graph(string inputFile);
	~Graph();

	void outputDistFromStartToEnd(string outputFile);
	
};

#endif