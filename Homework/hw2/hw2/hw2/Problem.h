#include <string>
#ifndef PROBLEM_H
#define PROBLEM_H

using namespace std;

class Problem
{
private:
public:
	string id = "000000";
	string name = "None";
	string difficulty_S = "Undefined";
	int difficulty_I = 0;

	Problem* previous = NULL;
	Problem* next = NULL;
	

	void diffConvert();
	
	Problem(string ID, string NAME, string DIFF);
	Problem();

};
#endif
