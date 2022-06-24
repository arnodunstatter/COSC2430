#include "ArgumentManager.h"
#include "RankSorters.h"

using namespace std;

int main(int argc, char** argv)
{
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	
	ofstream write(outputFile.c_str());

	RankSorters Data(inputFile, outputFile);
	
	return 0;
}