#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <direct.h>

void time_process(){
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    CreateProcess("Timer.exe", NULL, NULL, NULL, FALSE, 
				CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, 10000);
	TerminateProcess(pi.hProcess, 0);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void aProcess(){
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    CreateProcess("aProcess.exe", NULL, NULL, NULL, FALSE, 
				0, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, 10000);
	TerminateProcess(pi.hProcess, 0);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void createDir(){
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    CreateProcess("createDir.exe", NULL, NULL, NULL, FALSE, 
				0, NULL, NULL, &si, &pi);																																																																																																																																																																																											
	WaitForSingleObject(pi.hProcess, 10000);
	TerminateProcess(pi.hProcess, 0);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void list(){
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    CreateProcess("list.exe", NULL, NULL, NULL, FALSE, 
				0, NULL, NULL, &si, &pi);																																																																																																																																																																																											
	WaitForSingleObject(pi.hProcess, 10000);
	TerminateProcess(pi.hProcess, 0);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}



int main() {
    char cmd[100];
    


    while (1) {

        printf("Enter a command: ");
        scanf("%[^\n]%*c", cmd);

        if(strcmp(cmd, "time") == 0) time_process();
        else if(strcmp(cmd, "test") == 0) aProcess();
        else if(strcmp(cmd, "mkdir") == 0) createDir();
        else if(strcmp(cmd, "ls") == 0) list();
        else if(strcmp(cmd,"cd")){
        	char* buffer;
        	buffer = _getcwd( NULL, 0 );
        	printf("%s >", buffer);
		}
        else system(cmd);
    }
    return 0;
}

