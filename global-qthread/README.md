# global-qthread

The reason of crash is qt_message_print calls isEnabled on an instance QLoggingCategory::defaultCategory() which is a static global (Q_GLOBAL_STATIC) and destroys earlier.

###### build

```shell script
$ tar czf global-qthread.tgz global-qthread
$ recipetool create -o <path to>global-qthread.bb <path to>.tgz

$ tail -n12 <path to>global-qthread.bb
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "file:///mnt/<path to>/global-qthread.tgz"

S = "${WORKDIR}/${BPN}"

QMAKE_PROFILES = "${S}/global-qthread.pro"

inherit qmake5

OE_QMAKE_PATH_HEADERS = "${OE_QMAKE_PATH_QT_HEADERS}"
```

###### run

```shell script
~# ./global-qthread
thread 0xb6fc7220 app start
thread 0xb5fab450 log
[2021/03/03 11:59:21,536] foo
thread 0xb6fc7220 kill
SIGTERM received. Attempting to shutdown cleanly
Segmentation fault (core dumped)
```

###### debug

```shell script
~# gdbserver localhost:11111 ./global-qthread

$ gdb-multiarch ./global-qthread
Thread 1 "global-qthread" received signal SIGSEGV, Segmentation fault.
(gdb) bt
#0  0xb6e07ca8 in QLoggingCategory::isEnabled(QtMsgType) const ()
#1  0xb6d404b8 in qt_message_print(QtMsgType, QMessageLogContext const&, QString const&) ()
#2  0xb6d405b0 in qt_message(QtMsgType, QMessageLogContext const&, char const*, std::__va_list, QString&) ()
#3  0xb6d4074e in QMessageLogger::warning(char const*, ...) const ()
#4  0xb6d47c1c in QThread::~QThread() ()
#5  0xb6b25c88 in __run_exit_handlers
```
