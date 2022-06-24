#include <iostream>
#include <string>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

void search(string, ifstream&);
string decrypter(ifstream&);
void solver(string, ifstream&, ofstream&);

int main(int argc, char** argv)
{
	//argument manager setup
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	string start = "start";

	ifstream read;
	ofstream write;

	read.open(inputFile.c_str());
	if (!read.is_open())
		cout << inputFile << " was not opened\n";
	else
	{
		write.open(outputFile.c_str());
		if (!write.is_open())
			cout << outputFile << " was not opened\n";
		else
		{
			solver(start, read, write);
		}

	}


}

void search(string clue, ifstream& read)
{
	read.clear(); //clears eofbit flag
	read.seekg(0); //resets stream marker to beginning of file
	string line = "";
	while (line != clue)
	{
		read >> line;
	}
}

string decrypter(ifstream& read)
{
	string dimensions = ""; //will hold our dimensions as a string
	string symbol = ""; //will hold each symbol in our matrix
	int Row, Col;
	read >> dimensions;
	Row = stoi(dimensions.substr(0, 1));
	Col = stoi(dimensions.substr(2, 1));
	//now we create our matrix to receive data from input file
	string** matrix = new string * [Row]; //creates first dimension of 2D dynamic array, the list of rows
	for (int i = 0; i < Row; ++i) //creates each column 
		matrix[i] = new string[Col];

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
	bool** alreadyCovered = new bool* [Row]; //creates first dimension of 2D dynamic array, the list of rows
	for (int i = 0; i < Row; ++i) //creates each column 
		alreadyCovered[i] = new bool[Col];
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
		if (cP >= 0 && cP < Col && rP >= 0 && rP < Row && alreadyCovered[rP][cP] == 0)
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
				dir *= -1; //after we've moved in a row the direction gets reversed
			}
			moveCols = !moveCols; //each time we reach a boarder, we shift which dimension we're moving along
		}
		if (moveCols)
			cP += dir;
		else
			rP += dir;
	}

	return cypher;
}

void solver(string clue, ifstream& read, ofstream& write)
{
	if (clue == "finish")
		return;

	search(clue, read);
	string newClue = decrypter(read);
	solver(newClue, read, write);
	write << clue << endl;

}








/*
#include <iostream>
#include <string>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

void decoder(string, ifstream&, ofstream&);

int main(int argc, char ** argv)
{
	ArgumentManager am(argc, argv); //creates our ArgumentManager object, 'am'

	//these will get the input and output file names
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	string findMe = "start";

	ifstream read;
	ofstream write;

	read.open(inputFile.c_str()); //attempts to open the inputFile to read from
	if (read.is_open()) 
	{
		write.open(outputFile.c_str()); //if read file opened, then we attempt to open the outputFile to write to
		if (write.is_open()) 
		{
			decoder(findMe, read, write); //pass our read and write objects by reference to the decoder so that files don't have to be opened and closed over and over.
			write.close();
		}
		else
			cout << outputFile << " did not open properly.\n";

		read.close();
	}
	else
		cout << inputFile << " did not open properly.\n";
	return 0;
}

void decoder(string findMe, ifstream& read, ofstream& write)
{
	if (findMe == "finish") //base case
		return;


	string line ="", strRow, strCol; //will hold our line
	

	read.clear(); //clears eofbit flag
	read.seekg(0); //resets stream marker to beginning of file
	while (line != findMe) //searches for findMe
		read >> line;

	//now we get our matrix's dimension
	read >> line;
	strRow = line[0];
	strCol = line[2];
	//and load them into integer variables
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
				dir *= -1; //after we've moved in a row the direction gets reversed
			}
			moveCols = !moveCols; //each time we reach a boarder, we shift which dimension we're moving along
		}
		if (moveCols)
			cP += dir;
		else
			rP += dir;
	}
	
	decoder(cypher, read, write);

	write << findMe << endl;
		
	//now we deallocate
	for (int i = 0; i < Row; ++i)
		delete[] alreadyCovered[i];
	delete[] alreadyCovered;
		
	for (int i = 0; i < Row; ++i)
		delete [] matrix[i];
	delete [] matrix;
	
}
*/