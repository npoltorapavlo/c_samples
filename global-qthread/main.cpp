#include "signalhandler.h"
#include "logger.h"

#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QtGlobal>
#include <QCoreApplication>

#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    setupSignalHandlers();

    QCoreApplication a(argc, argv);

    qDebug() << "thread" << QThread::currentThreadId() << "app start";

    QMetaObject::invokeMethod(Logger::instance()->getHelper(), "log", Qt::QueuedConnection, Q_ARG(QString, "foo"));

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
    QTimer *timer = new QTimer();
    timer->setSingleShot(true);
    timer->setInterval(1000);
    QObject::connect(timer, &QTimer::timeout, [=]()
    {
        qDebug() << "thread" << QThread::currentThreadId() << "kill";
        kill(getpid(), SIGTERM);
        timer->deleteLater();
    });
    timer->start();
#else
    QTimer::singleShot(1000, &a, []()
    {
        qDebug() << "thread" << QThread::currentThreadId() << "kill";
        kill(getpid(), SIGTERM);
    });
#endif

    return a.exec();
}
