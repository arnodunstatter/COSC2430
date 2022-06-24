/*
#include "ArgumentManager.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
	//first we verify we have valid arguments
	//if (argc < 3)//must have 3 arguments, with main as the first
	//{
		//cout << "Must have at least 2 arguments after main" << endl;
		//return 0;
	//}

	ArgumentManager am(argc, argv); //creates our ArgumentManager object, 'am'

	//these will get the input and output file names
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	ifstream read;
	read.open(inputFile.c_str());

	ofstream write;
	write.open(outputFile.c_str());

	if (!(read.is_open() && write.is_open()))
		cout << "Input or output file didn't open.\n";
	else
	{
		string dummy;
		while (read >> dummy)
			write << dummy;

		read.close();
		write.close();
	}

}
*/