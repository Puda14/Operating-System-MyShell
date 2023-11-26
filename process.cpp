#include <windows.h>
#include <vector>
#include <string.h>
#include <iostream>
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
    printf("CreateProcess failed (%d).\n", GetLastError());
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
    printf("SetConsoleCtrlHandler failed (%d).\n", GetLastError());
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
    printf("CreateProcess failed (%d).\n", GetLastError());
    return;
  }

  // Wait until child process exits.
  WaitForSingleObject(process[numProcess].pi.hProcess, INFINITE);
  SetConsoleCtrlHandler(CtrlHandler, FALSE);

  return;
}

void listProcesses()
{
  if (numProcess == 0)
    cout << "Empty !" << endl;
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
      cout << process[index].imageName << endl;
    }
  }
}