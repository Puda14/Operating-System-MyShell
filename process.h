#ifndef PROCESS_H
#define PROCESS_H

#include <windows.h>
#include <string>

struct ProcessInfo
{
  PROCESS_INFORMATION pi;
  char imageName[101];
  DWORD pid;
  char sessionName[101];
  DWORD sessionNumber;
  SIZE_T memUsage;
  FILETIME creationTime;
  FILETIME exitTime;
  FILETIME kernelTime;
  FILETIME userTime;
};

void createProcessInBackGroundMode(const char s[]);
void createProcessInForeGroundMode(const char s[]);
void listProcesses();
void killAllProcess(char op[]);

#endif