#include "Servers.h"
#include <iostream>

using namespace std;

int main()
{
	int timer = 0; //in minutes
	int numOfServers, maxRunTime; //number of tellers, the length of the duration we want to simulate
	double avgNumCustPerMin; //average number of customers arriving per minute
	cout << "This program will model a bank service queue. To this end the user must enter some information about the bank being modeled.\n";
	cout << "How many tellers does the bank have? "; cin >> numOfServers;
	cout << "How many minutes should the simulation run? ";	cin >> maxRunTime;
	cout << "What is the average number of customers arriving per minute? "; cin >> avgNumCustPerMin;
	ServerList Bank(numOfServers, maxRunTime, avgNumCustPerMin);
}