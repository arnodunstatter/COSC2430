#include <iostream>
#include "list.h"
#include <vector>

int main()
{
	list ourList;
	vector<int> toAdd = { 2, 29, 11, 10, 48, 1, 33 };
	for (int i = 0; i < toAdd.size(); ++i)
	{
		ourList.adder(toAdd[i]);
	}

	ourList.printList();

	ourList.reverseLL(0);

	cout << endl;
	ourList.printList();
}