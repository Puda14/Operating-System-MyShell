#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

//#define S_IRUSR  0400
#define S_IRGRP  0040
#define S_IWGRP  0020
#define S_IXGRP  0010

#define S_IROTH  04
#define S_IWOTH  02
#define S_IXOTH  01


void printMenu(){
    printf("%s%25s%15s%15s\n", "Mode","LastWriteTime","Size","Name");
    printf("%s%25s%15s%15s\n", "----","-------------","----","----");
}

int main() {
    struct dirent *de;
    struct stat fileStat;
    char mode[10]; 

    DIR *dr = opendir(".");
    
    if (dr == NULL) {
        printf("ERROR");
        return 1;
    }
    
    printMenu();
    
    while ((de = readdir(dr)) != NULL) {
        char filename[256];
        strcpy(filename, de->d_name);
        
        if (stat(filename, &fileStat) == -1) {
            perror("stat");
            continue;
        }
        
        
        // Mode
        sprintf(mode, "%c%c%c%c%c%c%c",
                (S_ISDIR(fileStat.st_mode)) ? 'd' : '-',
                (fileStat.st_mode & S_IRUSR) ? 'r' : '-',
                (fileStat.st_mode & S_IWUSR) ? 'w' : '-',
                (fileStat.st_mode & S_IXUSR) ? 'x' : '-',
                (fileStat.st_mode & S_IRGRP) ? 'r' : '-',
                (fileStat.st_mode & S_IWGRP) ? 'w' : '-',
                (fileStat.st_mode & S_IXGRP) ? 'x' : '-');
        printf("%s", mode);
        
        
        // LastWriteTime
        struct tm *timeinfo;
        char formattedTime[20];
        timeinfo = localtime(&fileStat.st_mtime);
        strftime(formattedTime, sizeof(formattedTime), "%m/%d/%Y %I:%M %p", timeinfo);
        printf("%25s", formattedTime);
        
        
        // Size
        printf("%15ld", fileStat.st_size);
        
        // Name
        printf("%15s\n", filename);

    }
    
    closedir(dr);
    
    return 0;
}

