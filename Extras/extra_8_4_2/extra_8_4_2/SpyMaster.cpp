#include "SpyMaster.h"

SpyMaster::SpyMaster(int num) 
	: numOfSpies(num) {};

SpyMaster::~SpyMaster()
{
	delete[] secrets;
	delete[] spies;
}

void SpyMaster::secretsSetter(string secret, int index, Spy Present)
{
	secrets[index] = secret;
}

void SpyMaster::spiesSetter(string spy, int index)
{
	spies[index] = spy;
}