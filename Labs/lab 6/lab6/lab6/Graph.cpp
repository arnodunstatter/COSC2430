#include "Graph.h"



//Vertex////////////////////////////////////////////////////////////////////////////////////////////////////////
Vertex::Vertex(int i, int vertices)
	:Number(i) 
{
	//vector<bool> c(vertices, 0);
	//connections = c;

	//vector<int> d(vertices, 0);
	//distances = d;

	vector<pair<bool, int>> a(vertices, { 0,0 });
	adjacency = a;
};

int Vertex::numberOfConnections()
{
	int toReturn = 0;
	for (int i = 0; i < adjacency.size(); ++i)
	{
		if (adjacency[i].first == true)
			++toReturn;
	}
	return toReturn;
}


//Graph///////////////////////////////////////////////////////////////////////////////////////////////////////
Graph::Graph(string inputFile)//inputFile)
{
	ifstream read(inputFile);
	if (!read.is_open())
		cout << "Input file did not open correctly.\n";
	else
	{
		read >> vertices;
		read >> edges;
		read >> start;
		read >> end;
		--start;
		--end;

		//now let's initialize our graph's graph vector
		for (int i = 0; i < vertices; ++i)
			graph.push_back(new Vertex(i, vertices));

		//now we need to read in the connections and weights
		int from, to, dist;
		for (int i = 0; i < edges; ++i)
		{
			read >> from;
			read >> to;
			read >> dist;

			//first direction
			graph[from-1]->adjacency[to-1].first = true;
			graph[from-1]->adjacency[to-1].second = dist;

			//second direction
			graph[to-1]->adjacency[from-1].first = true;
			graph[to-1]->adjacency[from-1].second = dist;
		}

		read.close();
	}
}


Graph::~Graph()
{
	for (int i = 0; i < graph.size(); ++i)
	{
		delete graph[i];
	}
}

void Graph::outputDistFromStartToEnd(string outputFile)
{
	ofstream write(outputFile);
	if (!write.is_open())
		cout << "Output file did not open correctly.\n";
	else
	{
		write << dijkstra() << endl;
		write.close();
	}
}

int Graph::dijkstra()
{
	if (start == end)
		return 0;
	else
	{
		vector<pair<int, int>> connections(vertices, { 0,0 }); //first value will be connections explored, second value will be total connections
		//now let's count each vertex's connections and update the connections vector
		for (int i = 0; i < graph.size(); ++i)
			connections[i].second = graph[i]->numberOfConnections();
		
		//we consider start to be done so...
		//connections[start].first = connections[start].second;

		vector<int> distancesFromStart(vertices, 0); //will contain our distances
		distancesFromStart[start] = 0;
		int current = start;
		while (dijkstraNotDone(connections))
		{
			//first we go through the vertices current connects to and set their distances and update the connections vector
			for (int i = 0; i < graph[current]->adjacency.size(); ++i) //for each connection current has
			{
				if (current == 2 && i == 6)
					int i = 1;
				if (graph[current]->adjacency[i].first == true) //then current connects to vertex i
				{
					++connections[current].first;
					if (distancesFromStart[i] == 0 && connections[i].first == 0 && connections[i].second != 0) //then this is the first distance to the connection
					{
						distancesFromStart[i] = distancesFromStart[current] + graph[current]->adjacency[i].second; //set the distanceFromStart
						//++connections[i].first; //update the connections explored
					}
					else if (connections[i].first != connections[i].second)// && connections[i].first > 0)
					{
						int possibleNewDist = distancesFromStart[current] + graph[current]->adjacency[i].second;
						if (possibleNewDist < distancesFromStart[i])
							distancesFromStart[i] = possibleNewDist;
						//++connections[i].first;
					}

					if (connections[i].second == 1 && connections[i].first != 1)
						connections[i].first = 1;
				}
			}

			//now we update current
			current = indexOfClosestUncheckedVertex(graph[current]->adjacency, connections);
			if (current == -1)
				break;
		}
		return distancesFromStart[end];
	}	
}

bool Graph::dijkstraNotDone(vector<pair<int, int>> connections)
{
	for (int i = 0; i < connections.size(); ++i)
	{
		if (connections[i].first != connections[i].second)
			return true;
	}

	return false;
}

int Graph::indexOfClosestUncheckedVertex(const vector<pair<bool, int>> currentAdjacencyVector, const vector<pair<int, int>> connections)
{
	int min, minIndex = -1;
	for (int i = 0; i < currentAdjacencyVector.size(); ++i)
	{
		if (currentAdjacencyVector[i].first == true && connections[i].first != connections[i].second)
		{
			if (minIndex == -1)
			{
				minIndex = i;
				min = currentAdjacencyVector[i].second;
			}
			else if (currentAdjacencyVector[i].second < min)
			{
				min = currentAdjacencyVector[i].second;
				minIndex = i;
			}
		}
	}

	return minIndex;
}