#include "Problem.h"

Problem::Problem(string ID, string NAME, string DIFF)
:id(ID), name(NAME), difficulty_S(DIFF) 
{
	diffConvert();
}

Problem::Problem() {}

void Problem::diffConvert()
{
	if (difficulty_S == "Easy")
		difficulty_I = 1;
	else if (difficulty_S == "Medium")
		difficulty_I = 2;
	else if (difficulty_S == "Hard")
		difficulty_I = 3;
	else
		difficulty_I = 0;
}