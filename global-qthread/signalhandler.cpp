#include "signalhandler.h"

#include <QCoreApplication>

#include <signal.h>

void signalHandler(int signum)
{
    static bool bHandled = false;

    if (bHandled)
        return;

    bHandled = true;

    switch (signum)
    {
    case SIGTERM:
        printf("SIGTERM received. Attempting to shutdown cleanly\n");
        break;
    default:
        printf("Caught unknown signal %d in %s:%d\n", signum, __FILE__, __LINE__);
        break;
    }

    QCoreApplication* app = QCoreApplication::instance();
    if (app != NULL)
        app->exit(0);
}

void setupSignalHandlers()
{
    signal(SIGTERM, signalHandler);
}
