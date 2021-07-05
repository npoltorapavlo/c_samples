# c_samples

Code samples in C/C++.

# description

The table below lists the subdirectories and their description.

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| [destructed-twice](destructed-twice) | crash | 2 shared objects having the same global cause SEGV at exit |
| [global-qthread](global-qthread) | crash | Global QThread causes SEGV at exit |
| [no-virtual](no-virtual) | test | Override with/without virtual |
| [corrupt-stack](corrupt-stack) | crash | Thread in a dynamic library causes SEGV with ?? on dlclose |
| [usb-drive-listing](usb-drive-listing) | sample | App that uses libudev, mntent, and system paths to monitor USB drives |
| [sqlite-corrupt](sqlite-corrupt) | test | A thread-safe handling of the case when sqlite file is removed during an active connection |
| [read-write-lock](read-write-lock) | test | A lock that allows concurrent reads, but not writes |
| [url-origin](url-origin) | sample | Get URL origin sample |
| [wpeframework-test](wpeframework-test) | test | WPEFramework stress test |
| [wpeframework-errcode](wpeframework-errcode) | test | Common error codes in a simple WPEFramework client |
| [wpeframework-timer](wpeframework-timer) | crash | A crash due to a timer not finished before destructor |
| [quit-gmain-loop](quit-gmain-loop) | crash | GMainLoop in a dynamic library causes SEGV on dlclose |
| [named-semaphore](named-semaphore) | sample | POSIX named semaphore sample |
| [file-lock](file-lock) | sample | Shared mutex via flock |
| [rfcapi-test](rfcapi-test) | crash | Overflow in RFCapi |
| [iarm-init](iarm-init) | test | Test for IARM_Bus_Init concurrency |
| [sockets](sockets) | sample | Web, unix socket sample |
| [sysinfo-test](sysinfo-test) | test | Test code that uses sysinfo |

