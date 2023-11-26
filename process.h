#ifndef __PROCESS_H__
#define __PROCESS_H__

typedef struct{
    PROCESS_INFORMATION pi;  // Thông tin về quy trình
    std::string imageName;   // Tên của ảnh (Image Name)
    DWORD pid;               // Process ID (PID)
    std::string sessionName; // Tên phiên (Session Name)
    DWORD sessionNumber;      // Số phiên (Session#)
    SIZE_T memUsage;          // Sử dụng bộ nhớ (Mem Usage)
    FILETIME creationTime;    // Thời gian quy trình được tạo
    FILETIME exitTime;        // Thời gian quy trình kết thúc
    FILETIME kernelTime;      // Thời gian CPU sử dụng ở chế độ kernel
    FILETIME userTime;        // Thời gian CPU sử dụng ở chế độ người dùng
} ProcessInfo;
/* 
PROCESS_INFORMATION MEAN:

typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD  dwProcessId;
  DWORD  dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;


- hProcess: A handle to the newly created process. 
            The handle is used to specify the process in all functions 
            that perform operations on the process object.

- hThread: A handle to the primary thread of the newly created process.
            The handle is used to specify the thread in all functions 
            that perform operations on the thread object.

- dwProcessId: A value that can be used to identify a process. 
            The value is valid from the time the process is created until all
            handles to the process are closed and the process object is freed; 
            at this point, the identifier may be reused.

- dwThreadId: A value that can be used to identify a thread. The value is valid 
            from the time the thread is created until all handles to the 
            thread are closed and the thread object is freed; at this point, 
            the identifier may be reused.
*/

#endif