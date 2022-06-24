#ifndef SERVERS_H
#define SERVERS_H
#include <stdlib.h>
#include <time.h>
#include "Customer.h"
#include "Queue.cpp"
using namespace std;

class Server
{
	friend class ServerList;
private:
	string type; //what kind of business this teller deals with
	bool free = 1;

	Customer* helping = nullptr;

	Server* next = nullptr;

	Server(int);

};

class ServerList
{
	friend class Server;
private:
	int maxRunTime;
	double avgNumCustPerMin;
	int serverCount = 0;
	int timer = 0;
	bool needNewCust = 0;

	Queue<Customer*> deposits;
	Queue<Customer*> withdrawals;
	Queue<Customer*> transfers;

	Server* head = nullptr;
	Server* tail = nullptr;

public:
	ServerList(int, int, double); 
	
	void runSim();
	void newCustomersGetInLine();
	int newCustomersArrived(); //decides how many new customers arrived at a given time
	void NEXT(); //loads each server
	void run();
	
};
#endif