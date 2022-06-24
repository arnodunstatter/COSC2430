#include "PriorityQueue.h"
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char** argv)
{
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	ifstream read(inputFile.c_str());
	if (!read.is_open())
	{
		cout << "Input file did not open properly.\n";
		return 0;
	}
	//else...

	PriorityQueue PQ;

	//lets get all the input
	string line;
	while (getline(read, line))
	{
		PQ.push(line);
	}
	read.close();
	ofstream write(outputFile.c_str());
	if (!write.is_open())
	{
		cout << "Output file did not open properly.\n";
		return 0;
	}
	//else...
	
	while (!PQ.isEmpty())
	{
		write << PQ.frontTask() << endl;
		PQ.pop();
	}
	write.close();
}