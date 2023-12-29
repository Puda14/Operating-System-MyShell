#include <processthreadsapi.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <direct.h>
#include "process.h"
#include "dir_file.h"
#include "env.h"
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

void help();

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

		if (strcmp(key, "list") == 0)
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
		else if (strcmp(key, "stop") == 0)
		{
			stop(option);
		}
		else if (strcmp(key, "resume") == 0)
		{
			resume(option);
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
			else if(strcmp(type, "bat") == 0){
				runBat(file);
			}
		}
		else if(strcmp(key, "echo") == 0){
			
			if(option[0] == '%' && option[strlen(option)-1] == '%'){
				while (option[0] == '%')
					strcpy(&option[0], &option[1]);
				while (option[strlen(option) - 1] == '%')
					strcpy(&option[strlen(option) - 1], &option[strlen(option)]);
				readEnvironmentVariable(option);
			}
			else{
				printf("%s\n", option);
			}
		}
		else if(strcmp(key, "crf") == 0){
			createFile(option);
		}
		else if(strcmp(key, "delf") == 0){
			deleteFile(option);
		}
		else if(strcmp(key, "help") == 0){
			help();
		}
		else if(strcmp(key, "exit") == 0){
			return 0;
		}
		else{
			printf("\x1b[31m");
			printf("The term %s is not recognized as the name of a cmdlet\n", key);
			printf("You should use \"help\"\n");
			printf("\x1b[0m");
		}
	}
}

void help() {
	printf("\x1b[34m");
    printf("Tiny Shell Usage:\n");
    printf("  list                : List all processes\n");
    printf("  b                   : Create process in background mode\n");
    printf("  f                   : Create process in foreground mode\n");
    printf("  killA [-d]          : Kill all processes (optionally display details with -d)\n");
    printf("  kill [process name] : Kill a specific process\n");
    printf("  ls                  : List files and directories in the current directory\n");
    printf("  cd [directory]      : Change current directory to [directory]\n");
    printf("  clear               : Clear the console screen\n");
    printf("  [Drive]:            : Change current drive to [Drive]\n");
    printf("  mdir [directory]    : Create a new directory named [directory]\n");
    printf("  rmdir [directory]   : Remove the directory named [directory]\n");
    printf("  .\\file [-f|-b]      : Execute a file specified by .\\file with optional -f (foreground) or -b (background) option\n");
    printf("  echo [option]       : Display [option] or read an environment variable\n");
    printf("  crf [filename]      : Create a new file named [filename]\n");
    printf("  delf [filename]     : Delete the file named [filename]\n");
    printf("  exit                : Exit the shell\n");
	printf("\x1b[0m");
}