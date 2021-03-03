#include "logger.h"

#include <QThread>
#include <QDateTime>
#include <QDebug>
#include <QtGlobal>

Logger* Logger::s_instance = NULL;

#ifdef USE_QT_GLOBAL
Q_GLOBAL_STATIC(QThread, s_thread)
#elif USE_LOCAL_STATIC
QThread &s_thread()
{
    static QThread s;
    return s;
}
#else
static QThread s_thread; // global non-POD static
#endif

Logger::Logger(QObject* parent)
    : QObject(parent)
    , mHelper(new LoggerHelper)
{
}

Logger* Logger::instance()
{
    if (!s_instance)
    {
        s_instance = new Logger;
        QThread *t;
#ifdef USE_QT_GLOBAL
        t = s_thread;
#elif USE_LOCAL_STATIC
        t = &s_thread();
#else
        t = &s_thread;
#endif
        t->setObjectName(QLatin1String("logger"));
        s_instance->getHelper()->moveToThread(t);
        t->start();
    }
    return s_instance;
}

void LoggerHelper::log(const QString& s)
{
    qDebug() << "thread" << QThread::currentThreadId() << "log";
#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
    qDebug
#else
    qInfo
#endif
    ("[%s] %s", qPrintable(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz")), qPrintable(s));
}
