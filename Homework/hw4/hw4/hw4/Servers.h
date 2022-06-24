#ifndef SERVERS_H
#define SERVERS_H
#include "PriorityQueue.h"
#include "Process.h"

class Server;


class ServerList
{
	friend class Server;
private:
	int maxRunTime = 0;
	int processesToDo = 0;
	int serverCount = 0;
	int timer = 0;
	bool needToEject = 0;

	Server* head = nullptr;
	Server* tail = nullptr;
public:
	ServerList(string); //makes our server and the original queue
	Queue<Process*> toDoList;
	PriorityQueue done;

	void executeProcesses();
	bool notDone();
	void loadServers();
	void run();
	void eject();

	void output(string);
};




class Server
{
	friend ServerList;
private:
	//int maxRunTime = 0;
	int presentRunTime = 0;
	bool free = 1;
	Process* workingOn = nullptr;
	
	Server* next = nullptr;

	Server(int);
	
};
#endif
