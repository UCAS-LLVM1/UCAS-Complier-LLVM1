// RUN: %clang_cc1 -analyze -analyzer-checker=core,debug.ExprInspection -verify %s

void clang_analyzer_eval(bool);

typedef struct Opaque *Data;
struct IntWrapper {
  int x;
};

struct Child : public IntWrapper {
  void set() { x = 42; }
};

void test(Data data) {
  Child *wrapper = reinterpret_cast<Child*>(data);
  // Don't crash when upcasting here.
  // We don't actually know if 'data' is a Child.
  wrapper->set();
  clang_analyzer_eval(wrapper->x == 42); // expected-warning{{TRUE}}
}

namespace PR14872 {
  class Base1 {};
  class Derived1 : public Base1 {};

  Derived1 *f1();

  class Base2 {};
  class Derived2 : public Base2 {};

  void f2(Base2 *foo);

  void f3(void** out)
  {
    Base1 *v;
    v = f1();
    *out = v;
  }

  void test()
  {
    Derived2 *p;
    f3(reinterpret_cast<void**>(&p));
    // Don't crash when upcasting here.
    // In this case, 'p' actually refers to a Derived1.
    f2(p);
  }
}

namespace rdar13249297 {
  struct IntWrapperSubclass : public IntWrapper {};

  struct IntWrapperWrapper {
    IntWrapper w;
  };

  void test(IntWrapperWrapper *ww) {
    reinterpret_cast<IntWrapperSubclass *>(ww)->x = 42;
    clang_analyzer_eval(reinterpret_cast<IntWrapperSubclass *>(ww)->x == 42); // expected-warning{{TRUE}}

    clang_analyzer_eval(ww->w.x == 42); // expected-warning{{TRUE}}
    ww->w.x = 0;

    clang_analyzer_eval(reinterpret_cast<IntWrapperSubclass *>(ww)->x == 42); // expected-warning{{FALSE}}
  }
}

namespace PR15345 {
  class C {};

  class Base {
  public:
    void (*f)();
    int x;
  };

  class Derived : public Base {};

  void test() {
	Derived* p;
	*(reinterpret_cast<void**>(&p)) = new C;
	p->f();

    // We should still be able to do some reasoning about bindings.
    p->x = 42;
    clang_analyzer_eval(p->x == 42); // expected-warning{{TRUE}}
  };
}