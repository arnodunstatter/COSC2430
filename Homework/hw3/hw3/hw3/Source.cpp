#include "list.h"
#include <iostream>
#include "ArgumentManager.h"
#include "stack.cpp"



using namespace std;

int main(int argc, char** argv)
{
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string commandFile = am.get("command");
	string outputFile = am.get("output");

	list Expressions(inputFile, commandFile, outputFile);
}