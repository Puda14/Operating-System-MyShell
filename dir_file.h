#ifndef DIR_FILE_H
#define DIR_FILE_H

void listFilesAndDirectories();
void cd(const char *directoryName, char *buffer);
void changeDrive(char driveLetter, char *buffer);
void makeDir(char* dirName);
#endif