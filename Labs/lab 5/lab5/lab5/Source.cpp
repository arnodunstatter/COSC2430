#include <fstream>
#include <string>
#include <map>
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char** argv)
{
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	ifstream read(inputFile);
	if (!read.is_open())
	{
		cout << "Input file failed to open properly.\n";
		return 0;
	}//else...

	int size;
	read >> size;
	map<string, int> fruitCount;
	string text;
	for (int i = 0; i < size; ++i)
	{
		read >> text;
		fruitCount[text] += 1;
	}
	read.close();

	ofstream write(outputFile);
	if (!write.is_open())
	{
		cout << "Output file failed to open properly.\n";
		return 0;
	}//else...

	for (map<string, int>::const_iterator it = fruitCount.begin(); it != fruitCount.end(); ++it) 
		write << it->first << ": " << it->second << endl;
	write.close();
}