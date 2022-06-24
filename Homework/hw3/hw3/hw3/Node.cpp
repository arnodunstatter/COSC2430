#include "Node.h"

Node::Node(string t, string e)
	: type(t)
{
	expression = removeSpaces(e);
}

string Node::removeSpaces(string eWS) //eWS is "expression with spaces"
{
	string e = ""; //will be "expression without spaces" by the end
	for (int i = 0; i < eWS.length(); ++i)
	{
		if (eWS[i] != ' ')
			e += eWS[i];
	}
	return e;
}