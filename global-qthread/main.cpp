#include "signalhandler.h"
#include "logger.h"

#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>

#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    setupSignalHandlers();

    QCoreApplication a(argc, argv);

    qDebug() << "thread" << QThread::currentThreadId() << "app start";

    QMetaObject::invokeMethod(Logger::instance()->getHelper(), "log", Qt::QueuedConnection, Q_ARG(QString, "foo"));

    QTimer::singleShot(1000, &a, []()
    {
        qDebug() << "thread" << QThread::currentThreadId() << "kill";
        kill(getpid(), SIGTERM);
    });

    return a.exec();
}
