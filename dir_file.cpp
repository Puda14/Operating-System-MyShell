#include <windows.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
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

    printf("%-10s%-25s%-15s%-30s\n", "Mode", "LastWriteTime", "Length", "Name");
    printf("%-10s%-25s%-15s%-30s\n", "----", "-------------", "------", "-----");

    // Read and Show File and Dir
    while ((entry = readdir(dir)) != NULL)
    {
        // Get file/directory information
        stat(entry->d_name, &fileStat);

        // Print file/directory information
        printf("%-10o%-25s%-15ld%-30s\n\n", fileStat.st_mode, ctime(&fileStat.st_mtime), fileStat.st_size, entry->d_name);
    }

    // Close Dir
    closedir(dir);
}
