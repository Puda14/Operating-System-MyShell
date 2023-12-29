#include <windows.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include "dir_file.h"

using namespace std;

void cd(char *curDir)
{
}

void mkdir()
{
}

void rmdir()
{
}

void listFilesAndDirectories()
{
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    // Open Current Directory
    dir = opendir(".");

    if (dir == NULL)
    {
        perror("Error");
        return;
    }

    // Set width for formatting
    const int modeWidth = 10;
    const int timeWidth = 30;
    const int lengthWidth = 15;
    const int nameWidth = 30;

    cout << left << setw(modeWidth) << "Mode"
         << setw(timeWidth) << "LastWriteTime"
         << setw(lengthWidth) << "Length"
         << setw(nameWidth) << "Name" << endl;
    cout << left << setw(modeWidth) << "----"
         << setw(timeWidth) << "-------------"
         << setw(lengthWidth) << "------"
         << setw(nameWidth) << "-----" << endl;

    // Read and Show File and Dir
    while ((entry = readdir(dir)) != NULL)
    {
        // Get file/directory information
        stat(entry->d_name, &fileStat);

        // Convert ctime to a string for better formatting
        string timeStr = ctime(&fileStat.st_mtime);
        timeStr = timeStr.substr(0, timeStr.length() - 1); // Remove the newline character at the end

        // Print file/directory information
        cout << oct << left << setw(modeWidth) << fileStat.st_mode
             << setw(timeWidth) << timeStr
             << setw(lengthWidth) << fileStat.st_size
             << setw(nameWidth) << entry->d_name << endl
             << endl;
    }

    // Close Dir
    closedir(dir);
}
