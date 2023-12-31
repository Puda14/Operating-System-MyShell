# Operating-System-MyShell

## Project

**Giảng viên hướng dẫn:** Phạm Đăng Hải  
**Học phần:** Nguyên lý hệ điều hành  
**Mã học phần:** IT3070  
**Mã lớp:** 143573  
**Tên project:** Tiny Shell

**Mục Đích của Dự Án:**  
- Nghiên cứu các API quản lý tiến trình trong Windows
- Hiểu cách cài đặt và cách thức shell hoạt động.


## Members

| Họ và Tên      | MSSV     |
| --------------- | -------- |
| Phùng Tiến Đạt | 20210163 |
| Kha Minh Bảo    | 20210098 |
| Nguyễn Tuấn Đạt | 20225605 |

## Set up

1. Tải mã nguồn về máy

    ```sh
    git clone https://github.com/Puda14/Operating-System-MyShell.git
    ```

2. Cài đặt [chocolatey](https://chocolatey.org/install).

3. Cài đặt make:

    ```sh
    choco install make
    ```

4. Sau đó, tại thư mục chứa code chỉ cần soạn lệnh

    ```sh
    make
    ```

    để dịch chương trình

5. Sau đó,

    ```sh
    .\TinyShell
    ```

    để sử dụng

6. Sử dụng lệnh `help` để xem chi tiết các chức năng

## Document

- [CreateProcess](https://learn.microsoft.com/en-us/windows/win32/procthread/creating-processes)
- [mkdir](https://www.includehelp.com/c-programs/create-a-directory-using-mkdir-function.aspx#:~:text=Syntax%3A,%2C%20or%20-1%20on%20failure)
- [readdir](https://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html)
- [Scanning Directories](https://eslinuxprogramming.blogspot.com/2015/05/scanning-directories.html)
- [List Files and Directories](https://www.geeksforgeeks.org/c-program-list-files-sub-directories-directory/)
- [References](https://phantrung.files.wordpress.com/2017/01/bt-hdh-tuan-2.pdf)
- [Get Current Working Directory](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/getcwd-wgetcwd?view=msvc-170)
- [PROCESS_INFORMATION](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-process_information#syntax)
- [STARTUPINFOA](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-startupinfoa)
