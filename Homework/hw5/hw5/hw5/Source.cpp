#include "ArgumentManager.h"
#include "Btree.h"
#include <string>
#include <fstream>


using namespace std;

int main(int argc, char** argv)
{
	//obligatory argument manager instantiations
	ArgumentManager am(argc, argv);
	string commandFile = am.get("command");
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	//now lets read our commandFile
	ifstream read(commandFile);
	if (!read.is_open())
	{
		cout << "command file did not open properly.\n";
		return 0;
	} //else...
	//gets the degree
	string str;
	read >> str;
	str = str.substr(7);
	int degree = stoi(str); //this integer will be used to construct the Btree

	//gets the level
	vector<int> levels; //this integer will be used to output
	int num;
	while (read >> str)
	{
		read >> num;
		levels.push_back(num);
	}
		
	read.close(); //closes connection with commandFile
	
	//instantiate our Btree
	Btree BT(degree);

	read.open(inputFile);
	if (!read.is_open())
	{
		cout << "input file did not open properly.\n";
		return 0;
	} //else...

	while (read >> num)
		BT.insert(num, BT.getRoot());

	read.close();


	ofstream write(outputFile);
	if (!write.is_open())
	{
		cout << "output file did not open properly.\n";
		return 0;
	} //else...

	write << "Height=";
	write << BT.getHeight(BT.getRoot()) << endl;

	for (int i = 0; i < levels.size(); ++i)
	{
		BT.output(BT.getRoot(), 1, levels[i], write);
		write << endl;
	}
	
	write.close();

	return 0;
}

