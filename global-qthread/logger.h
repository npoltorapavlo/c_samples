#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class LoggerHelper;

class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger* instance();
    LoggerHelper* getHelper() { return mHelper; }
private:
    explicit Logger(QObject *parent = nullptr);
    static Logger* s_instance;
    LoggerHelper* mHelper;
};

class LoggerHelper : public QObject
{
    Q_OBJECT
public slots:
    void log(const QString& s);
};

#endif // LOGGER_H
