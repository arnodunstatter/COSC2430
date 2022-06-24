#include "Process.h"

Process::Process(int c, int t)
	:ProcessNumber(c), TotExecTime(t), ExecTimeLeft(t) {}

Process::~Process()
{
	delete this;
}