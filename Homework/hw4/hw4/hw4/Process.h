#ifndef PROCESS_H
#define PROCESS_H
using namespace std;

class Process
{
public:
	int ProcessNumber;
	int TotExecTime;
	int ExecTimeLeft;
	int start = -1; //flag
	int end = 0;
	int wait = 0;

	Process(int, int);
	~Process();
};
#endif


