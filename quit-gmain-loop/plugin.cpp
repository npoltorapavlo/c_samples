#include "plugin.h"

#include "service.h"
#include "pluginthread.h"

#include <glib.h>
#include <cstdio>
#include <unistd.h>

extern GMainLoop *Gloop;
static guint work_id = 0;

namespace {
  static gboolean work(gpointer data) {
    printf("%s\n", __FUNCTION__);
    sleep(1);
    printf("%s done\n", __FUNCTION__);
    return TRUE;
  }
}

__attribute__((constructor)) static void startUp (void) {
  printf("%s\n", __FUNCTION__);
}

SERVICE_REGISTER(Plugin, 1)

Plugin::~Plugin() {
  printf("%s\n", __FUNCTION__);

  DeInit();
}

void Plugin::Init() {
  printf("%s\n", __FUNCTION__);

  if(pluginThreadInit() == -1) {
    printf("thread init failed !!!\n");
  } else {
    pluginThreadStart();
  }

  printf("adding a sec timer\n");
  work_id = g_timeout_add_seconds(1, work, Gloop);
}

void Plugin::DeInit() {
  pluginThreadStop();
  pluginThreadTerm();
}
