#include <windows.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <psapi.h>

#include "process.h"

using namespace std;

ProcessInfo process[101];
int numProcess = 0;

void setImageNameOfProcess(const char s[])
{
  strcpy(process[numProcess].imageName, s);
}

void createProcessInBackGroundMode(const char s[])
{
  numProcess++;

  setImageNameOfProcess(s);
  STARTUPINFO si;

  si = {sizeof(STARTUPINFO)};
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(si);
  if (!CreateProcess(s,     // No module name (use command line)
                     NULL,  // Command line
                     NULL,  // Process handle not inheritable
                     NULL,  // Thread handle not inheritable
                     FALSE, // Set handle inheritance to FALSE
                     CREATE_NEW_CONSOLE,
                     NULL,                    // Use parent's environment block
                     NULL,                    // Use parent's starting directory
                     &si,                     // Pointer to STARTUPINFO structure
                     &process[numProcess].pi) // Pointer to PROCESS_INFORMATION structure
  )
  {
    printf("\x1b[31m");
    printf("CreateProcess failed (%d).\n", GetLastError());
    printf("\x1b[0m");
    return;
  }
}

// Console control handler function
BOOL CtrlHandler(DWORD fdwCtrlType)
{
  switch (fdwCtrlType)
  {
  case CTRL_C_EVENT:
    // Handle CTRL+C event
    if (numProcess > 0)
    {
      // Terminate the process to end it immediately
      TerminateProcess(process[numProcess].pi.hProcess, 0);
      // Close handles of the process
      CloseHandle(process[numProcess].pi.hThread);
      CloseHandle(process[numProcess].pi.hProcess);
      numProcess--;
    }
    return TRUE;
  }

  return FALSE;
}

void createProcessInForeGroundMode(const char s[])
{
  numProcess++;
  setImageNameOfProcess(s);
  STARTUPINFO si;

  si = {sizeof(STARTUPINFO)};
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(si);

  // Register the Ctrl+C handler function
  if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
  {
    printf("\x1b[31m");
    printf("SetConsoleCtrlHandler failed (%d).\n", GetLastError());
    printf("\x1b[0m");
    return;
  }
  if (!CreateProcess(s,     // No module name (use command line)
                     NULL,  // Command line
                     NULL,  // Process handle not inheritable
                     NULL,  // Thread handle not inheritable
                     FALSE, // Set handle inheritance to FALSE
                     CREATE_NEW_CONSOLE,
                     NULL,                    // Use parent's environment block
                     NULL,                    // Use parent's starting directory
                     &si,                     // Pointer to STARTUPINFO structure
                     &process[numProcess].pi) // Pointer to PROCESS_INFORMATION structure
  )
  {
    printf("\x1b[31m");
    printf("CreateProcess failed (%d).\n", GetLastError());
    printf("\x1b[0m");
    return;
  }

  // Wait until child process exits.
  WaitForSingleObject(process[numProcess].pi.hProcess, INFINITE);
  SetConsoleCtrlHandler(CtrlHandler, FALSE);

  return;
}

int getMemUsage(PROCESS_INFORMATION pi)
{

  PROCESS_MEMORY_COUNTERS_EX pmc;
  GetProcessMemoryInfo(pi.hProcess, (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
  return pmc.WorkingSetSize / 1024; // convert Byte to Kilobyte
}

string formatMemUsage(SIZE_T memUsage)
{
  return to_string(memUsage) + " K";
}

void listProcesses()
{
  if (numProcess == 0)
  {
    printf("\x1b[33m");
    cout << "Empty !" << endl;
    printf("\x1b[0m");
    return;
  }

  cout << setw(20) << left << "Image Name" << setw(20) << left << "Process Handle" << setw(20) << left << "Process ID" << setw(20) << left << "Mem Usage" << endl;

  cout << setw(20) << left << "==========" << setw(20) << left << "==============" << setw(20) << left << "==========" << setw(20) << left << "=========" << endl;

  for (int index = 1; index <= numProcess; index++)
  {
    DWORD dwExitCode;
    GetExitCodeProcess(process[index].pi.hProcess, &dwExitCode);
    if (dwExitCode != 259)
    {
      // Terminate the process to end it immediately
      TerminateProcess(process[index].pi.hProcess, 0);
      // Close process and thread handles.
      CloseHandle(process[index].pi.hThread);
      CloseHandle(process[index].pi.hProcess);
      for (int jChange = index; jChange < numProcess; jChange++)
      {
        process[jChange] = process[jChange + 1];
      }
      numProcess--;
      index--;
    }
    else
    {
      cout << setw(20) << left << process[index].imageName << setw(20) << left << process[index].pi.hProcess << setw(20) << left << process[index].pi.dwProcessId << setw(20) << left << formatMemUsage(getMemUsage(process[index].pi)) << endl;
    }
  }
}

void killAllProcess(char op[])
{
  printf("\x1b[33m");
  bool checkDetail = false;
  if (strcmp(op, "-d") == 0)
    checkDetail = true;
  for (int index = 1; index <= numProcess; index++)
  {
    TerminateProcess(process[index].pi.hProcess, 0);
    CloseHandle(process[index].pi.hThread);
    CloseHandle(process[index].pi.hProcess);
    if (checkDetail == true)
      cout << " >> KILLED " << process[index].pi.hProcess << endl;
  }
  cout << " ===> All process have been killed !" << endl;
  printf("\x1b[0m");
  numProcess = 0;
}

void kill(char op[])
{
  bool check = false;
  for (int index = 1; index <= numProcess; index++)
    if (strcmp(op, process[index].imageName) == 0)
    {
      check = true;
      TerminateProcess(process[index].pi.hProcess, 0);
      CloseHandle(process[index].pi.hThread);
      CloseHandle(process[index].pi.hProcess);
      for (int jChange = index; jChange < numProcess; jChange++)
      {
        process[jChange] = process[jChange + 1];
      }
      numProcess--;
      index--;
    }
  printf("\x1b[33m");
  if (check)
    cout << " ===> KILLED " << op << endl;
  else
    cout << " ===> " << op << " NOT FOUND" << endl;
  printf("\x1b[0m");
}

void stop(char *pName)
{
  bool check = false;
  for (int index = 1; index <= numProcess; index++)
  {
    if (strcmp(process[index].imageName, pName) == 0)
    {
      check = true;
      SuspendThread(process[index].pi.hThread);
      printf("\x1b[33m");
      printf("Stopped %s\n", pName);
      printf("\x1b[0m");
      break;
    }
  }
  if (!check)
  {
    printf("\x1b[31m");
    printf("%s NOT FOUND\n", pName);
    printf("\x1b[0m");
  }
}

void resume(char *pName)
{
  bool check = false;
  for (int index = 1; index <= numProcess; index++)
  {
    if (strcmp(process[index].imageName, pName) == 0)
    {
      check = true;
      ResumeThread(process[index].pi.hThread);
      printf("\x1b[33m");
      printf("Resumed %s\n", pName);
      printf("\x1b[0m");
      break;
    }
  }
  if (!check)
  {
    printf("\x1b[31m");
    printf("%s NOT FOUND\n", pName);
    printf("\x1b[0m");
  }
}