#include "pluginthread.h"

#include <glib.h>
#include <pthread.h>
#include <unistd.h>
#include <cstdio>

GMainLoop *Gloop = NULL;

pthread_t a_thread;
static guint a_source = 0;

void * Loop(void* data) {
  if (Gloop) {
    g_main_loop_run(Gloop);
    g_main_loop_unref(Gloop);
  }
  return nullptr;
}

int pluginThreadInit() {
  int result = 0;
  printf("%s\n", __FUNCTION__);
  Gloop = g_main_loop_new(NULL, FALSE);
  if (Gloop != NULL) {
    pthread_create(&a_thread, NULL, Loop, NULL);
  } else {
    printf("%s failed !!! \n", __FUNCTION__);
    result = -1;
  }
  return result;
}

int pluginThreadTerm() {
  int result = 0;
  printf("%s\n", __FUNCTION__);
  g_main_loop_quit(Gloop);
#ifdef JOIN_THREAD_ON_EXIT
  pthread_join(a_thread, NULL);
#endif
  return result;
}

static gboolean pluginThreadWork(gpointer data) {
  printf("%s\n", __FUNCTION__);
  sleep(1);
  printf("%s done\n", __FUNCTION__);
  return TRUE;
}

int pluginThreadStart() {
  int result = 0;
  printf("%s\n", __FUNCTION__);
  if (a_source == 0) {
    a_source = g_timeout_add(250, pluginThreadWork, Gloop);
  }
  return result;
}

int pluginThreadStop() {
  int result = 0;
  printf("%s\n", __FUNCTION__);
  if (a_source != 0) {
    g_source_remove(a_source);
    a_source = 0;
  }
  return result;
}
