#include <ostream>
#include <fstream>
#include <memory>

std::ofstream __TRACEFILE("TRACE.OUT");

#define __TRACE __TRACEFILE << typeid(*this).name() << "::" << __FUNCTION__ << std::endl;

class A {
private:
  class ResA {
  public:
    ResA() { __TRACE }
    ~ResA() { __TRACE }
  };
public:
  A() : m_res(new ResA)
  {
    __TRACE
    f1();
    f2();
  }
#ifdef USE_VIRTUAL
  virtual
#endif
  ~A() { __TRACE }
#ifdef USE_VIRTUAL
  virtual
#endif
  void f1() { __TRACE }
#ifdef USE_VIRTUAL
  virtual
#endif
  void f2() {
    __TRACE
    f1();
  }
private:
  std::unique_ptr<ResA> m_res;
};

class B : public A {
private:
  class ResB {
  public:
    ResB() { __TRACE }
    ~ResB() { __TRACE }
  };
public:
  B() : A(), m_res(new ResB)
  {
    __TRACE
    f1();
    f2();
  }
  ~B() { __TRACE }
  void f1() { __TRACE }
private:
  std::unique_ptr<ResB> m_res;
};

int main(int argc, char** argv) {
  {
    A a;
    a.f1();
    a.f2();
  }
  {
    B b;
    b.f1();
    b.f2();
  }
  {
    std::unique_ptr<A> p1(new B);
    p1->f1();
    p1->f2();

    auto p2 = static_cast<B*>(p1.get());
    p2->f1();
    p2->f2();
  }
  return 0;
}