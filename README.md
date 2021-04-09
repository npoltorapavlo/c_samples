# c_samples

Code samples in C/C++.

# description

The table below lists the subdirectories and their description.

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| [destructor-called-twice](destructor-called-twice) | crash | 2 linked shared objects containing the same global causing SEGV at exit |
| [global-qthread](global-qthread) | crash | Global QThread causing SEGV in QLoggingCategory at exit |
| [non-virtual-inherit](non-virtual-inherit) | experiment | Typical issues of overriding without virtual |
| [virtual-init](virtual-init) | experiment | A way to simulate the dynamic binding during initialization |
| [thread-corrupt-stack](thread-corrupt-stack) | crash | A thread is accessing a shared library which has been unloaded causing SEGV |
| [usb-drive-listing](usb-drive-listing) | experiment | App that uses libudev, mntent, and system paths to monitor USB drives |
| [sqlite-corrupt](sqlite-corrupt) | experiment | A thread-safe handling of the case when sqlite file is removed during an active connection |
| [read-write-lock](read-write-lock) | experiment | Allow concurrent reads, but lock all threads on write |
