#include "Servers.h"

ServerList::ServerList(string inputFile)
{
	ifstream read(inputFile.c_str());
	if (!read.is_open())
	{
		cout << "Input file did not open properly.\n";
		return;
	}
	//else...
	read >> maxRunTime;
	read >> processesToDo; //will actually get process number
	read >> serverCount; //actually gets server count


	//now we make our servers
	Server* newHead = new Server(maxRunTime);
	head = newHead;

	Server* cur = head;
	for (int i = 1; i <= serverCount - 1; ++i)
	{
		Server* newServer = new Server(maxRunTime);
		cur->next = newServer;
		cur = newServer;

		if (i == serverCount - 1)
			tail = cur;
	}


	//now we make our queue
	int execTime;
	int processNumber = 1;
	for (int i = 0; i < processesToDo; ++i)
	{
		read >> execTime;
		Process* addMe = new Process(processNumber, execTime);
		toDoList.push(addMe);
		processNumber++;
	}
	read.close();
}


void ServerList::executeProcesses()
{
	//check that they're all working
	while(notDone())
	{
		loadServers();
		while (needToEject == 0 && notDone())
			run();
		eject();
	}
}

bool ServerList::notDone()
{
	return done.size() != processesToDo;
}

void ServerList::loadServers()
{
	for (Server* cur = head; cur != nullptr; )
	{
		if (cur->free) //if the server is free, then we want to load it with a process
		{
			if (!toDoList.isEmpty())
			{
				if (toDoList.front()->TotExecTime == 0)
				{
					toDoList.front()->start = timer;
					toDoList.front()->end = timer;
					toDoList.front()->wait = timer;
					done.push(toDoList.front());
					toDoList.dequeue();
				}
				else
				{
					cur->workingOn = toDoList.front();
					toDoList.dequeue();
					cur->free = 0;
					cur->presentRunTime = 0;

					if (cur->workingOn->start == -1) //sets each process' start time, but only if it hasn't already been set
						cur->workingOn->start = timer;

					cur = cur->next;
				}
			}
			else
				return;
		}
		else
			cur = cur->next;
	}
}

void ServerList::run()
{
	//increment each servers' presentRunTime until it reaches maxRunTime
	//decrement each ExecTimeLeft until it reaches 0
	for (Server* cur = head; cur != nullptr; cur = cur->next)
	{
		if (cur->workingOn != nullptr)
		{
			--(cur->workingOn->ExecTimeLeft);
			++(cur->presentRunTime);
			if (cur->workingOn->ExecTimeLeft == 0 || cur->presentRunTime == maxRunTime)
			{
				cur->free = 1;
				needToEject = 1;
			}
		}
	}
	++timer;
}

void ServerList::eject()
{
	for (Server* cur = head; cur != nullptr; cur = cur->next)
	{
		if (cur->free && cur->workingOn != nullptr)
		{
			if (cur->workingOn->ExecTimeLeft > 0)
			{
				toDoList.push(cur->workingOn);
				cur->workingOn = nullptr;
			}
			else //it must be done
			{
				cur->workingOn->end = timer;
				cur->workingOn->wait = cur->workingOn->end - cur->workingOn->TotExecTime;

				done.push(cur->workingOn);
				cur->workingOn = nullptr;				
			}
		}
	}
	needToEject = 0;
}


void ServerList::output(string outputFile)
{
	ofstream write(outputFile.c_str());
	if (!write.is_open())
	{
		cout << "The output file failed to properly open.\n";
		return;
	}
	//else...
	write << "Max time: " << maxRunTime << endl;
	write << "Number of processes: " << processesToDo << endl;
	write << "Number of servers: " << serverCount << endl << endl;
	while (!done.isEmpty())
	{
		write << "Process: " << done.front()->ProcessNumber << endl;
		write << "Execution time: " << done.front()->TotExecTime << endl;
		write << "Wait Time: " << done.front()->wait << endl;
		write << "Start Time: " << done.front()->start << endl;
		write << "End Time: " << done.front()->end;
		done.dequeue();
		if (done.size() > 0)
			write << endl << endl;
		
	}
	write.close();
}




Server::Server(int maxRunTime)
	//:maxRunTime(maxRunTime) 
{}



