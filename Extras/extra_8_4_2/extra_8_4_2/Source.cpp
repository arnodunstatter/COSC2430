#include <string>
#include <iostream>
#include "SpyMaster.h"
#include "Spy.h"

using namespace std;

int main()
{
	int numOfSpies;
	
	cout << "Imagine you are a Spy Master...\n";
	cout << "How many spies work for you? ";
	cin >> numOfSpies;
	SpyMaster User(numOfSpies);

	cout << "Each spy must have a name and secret, and since you're the spy master, you must know them...so tell us...\n";
	Spy* list = new Spy[numOfSpies]; //creates a list of spies
	for (int i = 0; i < numOfSpies; ++i)
	{
		list[i].NameSetter(); //these two lines set each spy's name and secret
		list[i].SecretSetter();

		secretsSetter()

		//system("pause");
	}





	
	return 0;
}