#include "ArgumentManager.h"
#include "Servers.h"

int main(int argc, char** argv)
{
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	ServerList Servers(inputFile);
	Servers.executeProcesses();
	Servers.output(outputFile);
}