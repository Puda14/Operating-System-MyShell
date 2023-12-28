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
		char key[101];
		char option[101];
		scanf("%s",key);
		if (strcmp(key, "l") == 0)
		{
			listProcesses();
		}
		else if (strcmp(key, "b") == 0)
		{
			createProcessInBackGroundMode("Timer.exe");
		}
		else if (strcmp(key, "f") == 0)
		{
			createProcessInForeGroundMode("Timer.exe");
		}
		else if (strcmp(key, "killA") == 0){
			killAllProcess();
		}
		else {

		}
	}
}
