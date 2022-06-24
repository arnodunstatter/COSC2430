#include "ArgumentManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

int main(int argc, char** argv)
{
	//first we verify we have valid arguments
	if (argc < 3)//must have 3 arguments, with main as the first
	{
		cout << "Must have at least 2 arguments after main" << endl;
		return 0;
	}

	ArgumentManager am(argc, argv); //creates our ArgumentManager object, 'am'

	//these will get the input and output file names
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	string symb; //will hold each symbol as a string
	int num; //will hold each symbol as an int
	string condition = ""; //will hold our condition
	int conditionValue; //will hold our condition value if there is one
	int passCount = 0; //will hold the number of entries which satisfy our condition
	int tot; //will hold total number of entries in the matrix, i.e. m^2
	int m; //dimension of our m x m matrix
	double passRatio; //will hold the ratio of elements which pass relative to the overall number of elements (tot)
	double truncPR; //passRatio truncated to just the first 2 decimal places
	



	//now we get our data
	ifstream read; //establishes our read object
	read.open(inputFile.c_str()); //opens the input file

	//we will do a first pass to find out our dimensions and our condition
	if (read.is_open())
	{
		read >> symb;
		m = stoi(symb);
		tot = m * m;

		for (int i = 0; i < tot; ++i) //this should skip through the actual matrix to bring us to our condition
			read >> symb;

		while (read >> symb)
			condition += symb;

		if (condition.length() > 1) //this will format our condition variable. i.e. condition = ">6" gets converted to condition = ">" and conditionValue = 6
		{
			string temp = "";
			temp += condition[1];
			conditionValue = stoi(temp);
			condition = condition[0];
		}
		
		
		read.clear(); //resets eofbit, failbit, badbit
		read.seekg(1); //we want to reset the read marker so the next thing to be read is the first element in our matrix 

		for (int i = 0; i < tot; ++i) //now we will loop through our matrix and use our condition to evaluate each element and compute the number of elements which pass the condition (passCount)
		{
			read >> symb;
			num = stoi(symb);

			if (condition == "e")
			{
				if (num % 2 == 0)
					passCount++;
			}

			if (condition == "o")
			{
				if (num % 2 != 0)
					passCount++;
			}

			if (condition == "=")
			{
				if (num == conditionValue)
					passCount++;
			}

			if (condition == ">")
			{
				if (num > conditionValue)
					passCount++;
			}

			if (condition == "<")
			{
				if (num < conditionValue)
					passCount++;
			}
		}

		passRatio = passCount / static_cast<double>(tot); //now we must round
		if (static_cast<int>(passRatio * 1000) % 10 >= 5) //if true, we must round up, else we don't have to round
			passRatio += 0.01;
		
		read.close(); //we must close our inputFile

		//now we output
		ofstream write; //creates our write object
		write.open(outputFile.c_str()); //opens our output file
		if (write.is_open())
		{
			write << fixed << setprecision(2) << passRatio; //outputs our passRatio
			write.close(); //closes our output file
		}
		else
			cout << outputFile << " failed to open properly.\n";
	}
	else
		cout << inputFile << " failed to open properly.\n";


	
	return 0;
}