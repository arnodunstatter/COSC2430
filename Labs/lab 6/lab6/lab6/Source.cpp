#include "Graph.h"
#include "ArgumentManager.h"


using namespace std;

int main(int argc, char** argv)
{
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	Graph g(inputFile);
	g.outputDistFromStartToEnd(outputFile);
}