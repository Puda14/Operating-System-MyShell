#include <processthreadsapi.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <direct.h>
#include "process.h"
#include "dir_file.h"
using namespace std;

void makeStandardCmd(char s[])
{
	while (s[0] == ' ')
		strcpy(&s[0], &s[1]);
	while (s[strlen(s) - 1] == ' ')
		strcpy(&s[strlen(s) - 1], &s[strlen(s)]);
	for (int i = 0; i < strlen(s); i++)
		if ((s[i] == ' ') && (s[i + 1] == ' '))
		{
			strcpy(&s[i], &s[i + 1]);
			i--;
		}
}

void getKey(char s[], char key[])
{

	int spaceIndex = 0;

	// Find the position of the first space in the string s
	while (s[spaceIndex] != ' ' && s[spaceIndex] != '\0')
	{
		key[spaceIndex] = s[spaceIndex];
		spaceIndex++;
	}
	key[spaceIndex] = '\0';
}

void getOption(char s[], char option[])
{

	// Find the position of the first space in the string s
	int spaceIndex = 0;
	while (s[spaceIndex] != ' ' && s[spaceIndex] != '\0')
	{
		spaceIndex++;
	}

	// Copy the content from position spaceIndex + 1 to the end of the string into option
	int optionIndex = 0;
	while (s[spaceIndex + 1] != '\0')
	{
		option[optionIndex] = s[spaceIndex + 1];
		spaceIndex++;
		optionIndex++;
	}
	option[optionIndex] = '\0'; // End the option string
}

int main()
{

	char *buffer = _getcwd(NULL, 0);

	while (1)
	{

		printf("%s>", buffer);

		char key[101] = "\0";
		char option[101] = "\0";
		char cmd[101] = "\0";

		scanf("%[^\n]%*c", cmd);
		makeStandardCmd(cmd);
		getKey(cmd, key);
		getOption(cmd, option);

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
		else if (strcmp(key, "killA") == 0)
		{
			killAllProcess(option);
		}
		else if (strcmp(key, "kill") == 0)
		{
			kill(option);
		}
		else if (strcmp(key, "ls") == 0)
		{
			listFilesAndDirectories();
		}
		else if(strcmp(key, "cd") == 0){
			cd(option, buffer);
		}
		else if(strcmp(key, "clear") == 0){
			system("cls");
		}
		else if('A'<=key[0]&&key[0]<='Z'&&key[1] == ':'){
			changeDrive(key[0], buffer);
		}
		else if(strcmp(key, "mdir") == 0){
			makeDir(option);
		}
		else if(strcmp(key, "rmdir") == 0){
			removeDir(option);
		}
		else if(key[0] == '.' && key[1] == '\\'){

			char *file;
			strcpy(file, key+2);

			char* lastDot = strrchr(key, '.');
			char type[10];// Type of file
			
			if (lastDot != nullptr) {
        		sscanf(lastDot + 1, "%99s", type);  
   			} else {
        		printf("Unable to read file type");
    		}

			if(strcmp(type, "exe") == 0) runExe(file, option);
		}
		else{
		}
	}
}
