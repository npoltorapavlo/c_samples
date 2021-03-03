#include "logger.h"

#include <QThread>
#include <QDateTime>
#include <QDebug>
#include <QtGlobal>

Logger* Logger::s_instance = NULL;

static QThread s_thread; // non-POD static

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
        s_thread.setObjectName(QLatin1String("logger"));
        s_instance->getHelper()->moveToThread(&s_thread);
        s_thread.start();
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
