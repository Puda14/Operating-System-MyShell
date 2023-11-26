#include <processthreadsapi.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "process.h"
using namespace std;

int main()
{
	printf("Check!\n");

	while (1)
	{
		char k;
		cin >> k;
		if (k == 'l')
		{
			listProcesses();
		}
		else if (k == 'b')
		{
			createProcessInBackGroundMode("Timer.exe");
		}
		else if (k == 'f')
		{
			createProcessInForeGroundMode("Timer.exe");
		}
	}
}
