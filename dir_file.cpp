#include <windows.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <ctime>
#include <string>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <direct.h>
#include <unistd.h>
#include "dir_file.h"
#include "process.h"

using namespace std;

void cd(const char *directoryName, char *buffer) {
    if (_chdir(directoryName) == 0) {
        _getcwd(buffer, _MAX_PATH);
    } else {
        perror("Error");
    }
}

void changeDrive(char driveLetter, char *buffer) {
    char path[4];
    path[0] = driveLetter;
    path[1] = ':';
    path[2] = '\\';
    path[3] = '\0';

    if (_chdir(path) == 0) {
        _getcwd(buffer, _MAX_PATH);
    } else {
        perror("Error");
    }
}


void makeDir(char* dirName)    
{
    if (mkdir(dirName) == 0)
        printf("Directory created successfully\n");
    else
        printf("Unable to create directory %s\n", dirName);
}

void removeDir(const char* dirName) {

    if (rmdir(dirName) == 0)
        printf("Directory removed successfully\n");
    else
        printf("Unable to remove directory %s\n", dirName);
}

void listFilesAndDirectories() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    // Open the current directory
    dir = opendir(".");

    if (dir == NULL) {
        perror("Error");
        return;
    }

    // Set width for formatting
    const int modeWidth = 10;
    const int timeWidth = 30;
    const int lengthWidth = 15;
    const int nameWidth = 30;

    // Print header row
    cout << left << setw(modeWidth) << "Mode"
         << setw(timeWidth) << "LastWriteTime"
         << setw(lengthWidth) << "Length"
         << setw(nameWidth) << "Name" << endl;
    cout << left << setw(modeWidth) << "----"
         << setw(timeWidth) << "-------------"
         << setw(lengthWidth) << "------"
         << setw(nameWidth) << "-----" << endl;

    // Read and show file and directory information
    while ((entry = readdir(dir)) != NULL) {
        // Get file/directory information
        stat(entry->d_name, &fileStat);

        // Convert ctime to a string for better formatting
        string timeStr = ctime(&fileStat.st_mtime);
        timeStr = timeStr.substr(0, timeStr.length() - 1); // Remove the newline character at the end

        // Use st_size for file size in bytes
        double fileSize = fileStat.st_size;

        // Print file/directory information
        cout << oct << left << setw(modeWidth) << fileStat.st_mode
             << setw(timeWidth) << timeStr
             << fixed << setw(lengthWidth) << setprecision(0) << fileSize
             << setw(nameWidth) << entry->d_name << endl;
    }

    // Close the directory
    closedir(dir);
}

void runExe(char* exePath, char* option){
    if (strcmp(option, "-f") == 0) {
        createProcessInForeGroundMode(exePath);
    } else if (strcmp(option, "-b") == 0 || strcmp(option, "\0") == 0) {
        createProcessInBackGroundMode(exePath);
    } else {
        perror("Error");
    }
}

void runBat(char* batchFilePath){

    if (system(batchFilePath) == 0) {
        printf("Run Successfully\n");
    } else {
        perror("Error");
    }
}

void createFile(char* fileName){
    
    FILE *file = fopen(fileName, "w");

    if (file != NULL) {
        printf("File created successfully: %s\n", fileName);
        fclose(file);
    } else {
        perror("Error creating file");
    }
}

void deleteFile(char* fileName){

    if (remove(fileName) == 0) {
        printf("File deleted successfully: %s\n", fileName);
    } else {
        perror("Error deleting file");
    }
}