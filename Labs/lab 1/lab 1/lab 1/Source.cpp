#include <string>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char** argv)
{
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string outputFile = am.get("output");
	string fnf = "ERROR: File not found";
	string nr = "ERROR: negative result";

	ifstream read(inputFile.c_str());
	ofstream write(outputFile.c_str());

	try { //tries to read from file, but if file isn't open we throw to our catch which writes the fnf error
		if (!read.is_open())
			throw fnf;

		char operation, first, second; //will hold our input from the inputFile
		int result; //will hold the result of our operation

		//now we load our inputs into our variables
		read >> operation;
		read >> first;
		read >> second;

		//we are done reading so we can close our inputFile
		read.close();

		//now we compute our result
		if (operation == '1')
			result = static_cast<int>(first) + static_cast<int>(second);
		else if (operation == '2')
			result = static_cast<int>(first) - static_cast<int>(second);
		
		
		try { //tries to write our result, but if result is negative we throw to our catch which writes the nr error
			if (result < 0)
				throw nr;
			write << result;
		}
		catch (string nr)
		{
			write << nr;
		}

		
	}
	catch (string fnf)
	{
		write << fnf;
	}
	
	//we are done writing so we can close the outputFile
	write.close();

	return 0;
}