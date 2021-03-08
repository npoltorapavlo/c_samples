# c_samples

Code samples in C/C++.

# description

The table below lists the subdirectories and their description.

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| [destructor-called-twice](destructor-called-twice/README.md) | crash | 2 linked shared objects containing the same global causing SEGV at exit |
| [global-qthread](global-qthread/README.md) | crash | Global QThread causing SEGV in QLoggingCategory at exit |
| [non-virtual-inherit](non-virtual-inherit/README.md) | experiment | Typical issues of overriding without virtual |
| [virtual-init](virtual-init/README.md) | experiment | A way to simulate the dynamic binding during initialization |
| [thread-corrupt-stack](thread-corrupt-stack/README.md) | crash | A thread is accessing a shared library which has been unloaded causing SEGV |
