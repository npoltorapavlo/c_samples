#include <a.h>

#include <b.h>

int main(int argc, char** argv) {
  {
    A a;
    a.print();
  }
  {
    B b;
    b.print();
  }
  return 0;
}