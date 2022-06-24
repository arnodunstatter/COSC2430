#include "ArgumentManager.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void decoder(string, string, string);

int main(int argc, char ** argv)
{
	ArgumentManager am(argc, argv); //creates our ArgumentManager object, 'am'

	//these will get the input and output file names
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	string findMe = "start";
	ofstream write;

	decoder(findMe, inputFile, outputFile); 

}

void decoder(string findMe, string inputFile, string outputFile)//, ifstream read, ofstream write)
{
	if (findMe == "finish") //base case
		return;

	ifstream read;
	read.open(inputFile.c_str());

	string line ="", strRow, strCol; //will hold our line
	

	if (!read.is_open())
		cout << inputFile << " didn't open properly.\n";
	else
	{
		while (line != findMe)
			read >> line;
		read >> line;
		strRow = line[0];
		strCol = line[2];
		int Row = stoi(strRow);
		int Col = stoi(strCol);


		//now we create our matrix to receive data from input file
		string** matrix = new string * [Row]; //creates first dimension of 2D dynamic array, the list of rows
		for (int i = 0; i < Row; ++i) //creates each column 
			matrix[i] = new string [Col];

		//now we load the matrix
		for (int r = 0; r < Row; ++r)
		{
			for (int c = 0; c < Col; ++c)
			{
				read >> matrix[r][c];
			}
		}
		
		//now we decrypt the matrix
		string cypher = ""; //this will hold the decrypted word
		int rP = 0; //row position, initialized at 0
		int cP = 0; //column position, initialized at 0
		int dir = 1; //direction of movement within the matrix
		bool moveCols = 1; //1 if we're shifting cols, 0 if we're shifting rows

		//the following matrix will hold boolean values that reflect whether the corresponding letter in the original matrix
		//has already been added to cypher
		bool** alreadyCovered = new bool * [Row]; //creates first dimension of 2D dynamic array, the list of rows
		for (int i = 0; i < Row; ++i) //creates each column 
			alreadyCovered[i] = new bool [Col];
		//now we set them all to false
		for (int r = 0; r < Row; ++r)
		{
			for (int c = 0; c < Col; ++c)
			{
				alreadyCovered[r][c] = 0;
			}
		}

		//this navigates the spiral matrices to form the cypher/clue
		while (cypher.length() < Row * Col) 
		{
			if (cP < Col && rP < Row && alreadyCovered[rP][cP] == 0)
			{
				cypher += matrix[rP][cP];
				alreadyCovered[rP][cP] = 1; //now that it's been covered (included in cypher)

			}
			else
			{
				if (moveCols)
					cP -= dir;
				else
				{
					rP -= dir;
					dir *= -1;
				}
				moveCols = !moveCols; //each time we reach a boarder, we shift which dimension we're moving along
			}
			if (moveCols)
				cP += dir;
			else
				rP += dir;
		}

		read.close(); //closes our inputFile
		
		decoder(cypher, inputFile, outputFile);

		ofstream write;
		write.open(outputFile.c_str(), ios_base::app);
		if (!write.is_open())
			cout << outputFile << " did not open properly.\n";
		else
		{
			write << findMe << endl;
			write.close();
		}
		
		
		//now we deallocate
		for (int i = 0; i < Row; ++i)
			delete[] alreadyCovered[i];
		delete[] alreadyCovered;
		
		for (int i = 0; i < Row; ++i)
			delete [] matrix[i];
		delete [] matrix;
		
		
	}
}