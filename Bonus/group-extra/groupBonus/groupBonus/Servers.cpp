#ifndef SERVERS_CPP
#define SERVERS_CPP
#include "Servers.h"

Server::Server(int counter)
{
	int decider = counter % 3; //decider will only ever be 0, 1, or 2
	switch (decider) //establishes what type of server it is
	{
	case 0:
		type = "deposit";
		break;
	case 1:
		type = "withdrawal";
		break;
	case 2:
		type = "transfer";
		break;
	}
}





ServerList::ServerList(int size, int maxRunTime, double avgNumCustPerMin)
	:maxRunTime(maxRunTime), avgNumCustPerMin(avgNumCustPerMin)
{
	int i = 0; //will be used to give types to each server
	head = new Server(i);
	Server* cur = head;
	for (++i; i < size; ++i, cur = cur->next)
	{
		cur->next = new Server(i);
	}
	tail = cur;
}

void ServerList::runSim()
{
	newCustomersGetInLine(); //gets each new customer into their appropriate line
	NEXT(); //tellers get customers to help
	while (timer != maxRunTime)
		run();

}

void ServerList::newCustomersGetInLine()
{
	int numNewCust = newCustomersArrived();
	for (int i = 0; i < numNewCust; ++i) //generates each new customer and places it into the appropriate queue
	{
		Customer* newCust = new Customer(timer);
		newCust->startQ = timer;

		if (newCust->business == "deposit")
			deposits.push(newCust);
		else if (newCust->business == "withdrawal")
			withdrawals.push(newCust);
		else if (newCust->business == "transfer")
			transfers.push(newCust);
			
	}
}

int ServerList::newCustomersArrived()
{
	//this needs to be changed later to use poisson distribution
	//but for now we'll just return the either either the floor or ceiling 
	//of the avgNumCustPerMin
	srand(time(NULL));
	int decider = rand() % 2; //will either be 0 or 1
	int toReturn;
	if (decider == 0) //return floor
		toReturn = avgNumCustPerMin;
	else //return ceiling
		toReturn = avgNumCustPerMin + 1;

	return toReturn;
}

void ServerList::NEXT()
{
	for (Server* cTeller = head; cTeller != nullptr; cTeller = cTeller->next)
	{
		if (cTeller->helping != nullptr) //then the server can help a new customer
		{
			if (cTeller->type == "deposit" && !deposits.isEmpty())
			{
				cTeller->helping = deposits.front();
				deposits.dequeue();
			}
			else if (cTeller->type == "withdrawal" && !withdrawals.isEmpty())
			{
				cTeller->helping = withdrawals.front();
				withdrawals.dequeue();
			}
			else if (cTeller->type == "transfer" && !transfers.isEmpty())
			{
				cTeller->helping = transfers.front();
				transfers.dequeue();
			}
			//else all queues must be empty, so no point in checking the next server
			else return;
		}
	}
}

void ServerList::run()
{
	for (Server* cTeller = head; cTeller != nullptr; cTeller = cTeller->next)
	{
		if (cTeller->helping != nullptr)
		{
			--(cTeller->helping->processingTimeLeft);
			if (cTeller->helping->processingTimeLeft == 0)
			{
				needNewCust = 1;
			}
		}
	}
	++timer;
}
#endif
