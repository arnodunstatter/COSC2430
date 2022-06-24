#ifndef Spy_h
#define Spy_h
#include <string>
#include <iostream>

using namespace std;

class Spy
{
private:
	string secret, name;
public:
	
	void NameSetter(); //sets name
	void SecretSetter(); //secret name

	friend class SpyMaster; //do i need the "class" keyword here?
	
};

#endif