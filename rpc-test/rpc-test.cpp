#include "authclient.h"

int main(int argc, char** argv) {
  TestAuth("/tmp/SecurityAgent/token", "SecurityAgent");

  return 0;
}
