#include "Customer.h"

//the constructor will receive a startQ,
//it will also use a random number generator
//to assign a what the customer's business is

Customer::Customer(int startQ)
	:startQ(startQ)
{
	srand(time(NULL));
	int decider = rand() % 3; // can be 0, 1, or 2
	switch (decider)
	{
	case 0:
		business = "deposit";
		processingTimeLeft = 5;
		break;
	case 1:
		business = "withdrawal";
		processingTimeLeft = 7;
		break;
	case 2:
		business = "transfer";
		processingTimeLeft = 10;
		break;
	}
}