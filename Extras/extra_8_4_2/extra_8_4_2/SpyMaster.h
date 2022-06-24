#ifndef SpyMaster_h
#define Spymaster_h
#include <string>
#include <iostream>

using namespace std;

class SpyMaster
{
private:
	string* secrets = new string [numOfSpies];
	string* spies = new string [numOfSpies];
public:
	int numOfSpies = 1;
	
	//constructor and destructor
	SpyMaster(int num);
	~SpyMaster();

	//mutators
	void secretsSetter(string secret, int index, Spy present);
	void spiesSetter(string spy, int index);
};

#endif