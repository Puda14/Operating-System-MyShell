#ifndef DIR_FILE_H
#define DIR_FILE_H

void listFilesAndDirectories();
void cd(const char *directoryName, char *buffer);
void changeDrive(char driveLetter, char *buffer);
void makeDir(char* dirName);
void removeDir(const char* dirName);
void runExe(char* exePath, char* option);
void runBat(char* batchFilePath);
void createFile(char* fileName);
void deleteFile(char* fileName);
#endif