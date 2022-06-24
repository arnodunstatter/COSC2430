#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <stdlib.h>
#include <time.h>
//#include "Servers.h" //compiler doesn't like the circular include

using namespace std;

class Customer
{
	friend class Server;
	friend class ServerList;
private:
	int number;
	int startQ; //when they join the queue
	int waitTime; //how long they waited in the queue
	int processingTimeLeft; //how long their task takes
	int leaveTime; //startQ + waitTime + processingTime

	string business;


	Customer(int);

};
#endif
