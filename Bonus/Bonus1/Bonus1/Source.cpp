#include "List.h"
#include "Node.h"

using namespace std;

bool isInt(string);


int main()
{
	string temp; //just a dummy, will be changed;


	List first;
	cout << "Enter the first linked list by entering an integer and pressing enter and then the next number, and so on.\n";
	cout << "Enter a letter to end the input into the first list.\n";
	while (isInt(temp))
	{
		cin >> temp;
		first.adder(temp);
	}
	cout << endl;



	temp = "1";
	List second;
	cout << "Enter the second linked list by entereing an integer and pressing eneter and then the next number, and so on.\n";
	cout << "Enter a letter to end the input into the second list.\n";
	while (isInt(temp))
	{
		cin >> temp;
		second.adder(temp);
	}
	cout << endl;


	
	List firstPlusSecond(first, second);
	cout << "Combining the two lists yields the following:\n";
	firstPlusSecond.printList(); cout << endl;
	
	
}

bool isInt(string line)
{
	for (int i = 0; i < line.length(); i++)
	{
		if (!isdigit(line[i])) return false; //if we find any non-digit then we return false
	}

	//if we make it through the string and we've only found digits then we return true
	return true;
}

