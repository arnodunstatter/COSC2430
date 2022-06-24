#include "Node.h"

Node::Node(string expression) //parameter constructor
	:expression(expression)
{
	evaluator(expression);
}

Node::Node(Node* copyMe) //copy constructor
{
    previous = copyMe->previous;
    next = copyMe->previous;
    expression = copyMe->expression;
    evaluated = copyMe->evaluated;
    expressionIsGood = copyMe->expressionIsGood;
}

void Node::copy(Node* copyMe)
{	
	
	previous = copyMe->previous;
	next = copyMe->previous;
	expression = copyMe->expression;
	evaluated = copyMe->evaluated;
	expressionIsGood = copyMe->expressionIsGood;
}

void Node::evaluator(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i])) //if we find any non-digit then we set expressionIsGood to false and return
		{
			expressionIsGood = false;
			return;
		}
	}

	//if we make it through the string and we've only found digits then we return true
	expressionIsGood = true;
	evaluated = stoi(str);
}