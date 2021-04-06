#include <ostream>
#include <fstream>
#include <memory>

#ifdef USE_VIRTUAL
#define SPECIFIER virtual
#else
#define SPECIFIER
#endif

std::ofstream TRACEFILE("TRACE.OUT");

#define TRACE TRACEFILE << __FUNCTION__ << ' ';
#define TRACE1(s) TRACEFILE << s << ' ';
#define TRACE_ENDL TRACEFILE << std::endl;

class A {
private:
  class Ar {
  public:
    Ar() { TRACE }
    ~Ar() { TRACE }
  };
public:
  A() : m_res(new Ar)
  {
    TRACE
    _1();
    _2();
  }
  SPECIFIER ~A() { TRACE }
  SPECIFIER void _1() { TRACE1("A1") }
  SPECIFIER void _2() {
    TRACE1("A2 ->")
    _1();
  }
private:
  std::unique_ptr<Ar> m_res;
};

class B : public A {
private:
  class Br {
  public:
    Br() { TRACE }
    ~Br() { TRACE }
  };
public:
  B() : A(), m_res(new Br)
  {
    TRACE
    _1();
    _2();
  }
  ~B() { TRACE }
  void _1() { TRACE1("B1") }
private:
  std::unique_ptr<Br> m_res;
};

int main(int argc, char** argv) {
  {
    A a;
    a._1();
    a._2();
  }
  TRACE_ENDL
  {
    B b;
    b._1();
    b._2();
  }
  TRACE_ENDL
  {
    std::unique_ptr<A> p1(new B);
    p1->_1();
    p1->_2();
  }
  TRACE_ENDL
  return 0;
}