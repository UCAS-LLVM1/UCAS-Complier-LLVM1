// RUN: %clang_cc1 -emit-llvm -o - %s | FileCheck %s
// pr6644

extern "C" {
  namespace N {
    struct X { 
      virtual void f();
    };
    void X::f() { }
  }
}

// CHECK: define void @_ZN1N1X1fEv

extern "C" {
  static void test2_f() {
  }
  // CHECK: define internal void @_Z7test2_fv
  static void test2_f(int x) {
  }
  // CHECK: define internal void @_Z7test2_fi
  void test2_use() {
    test2_f();
    test2_f(42);
  }
}

extern "C" {
  struct test3_s {
  };
  bool operator==(const int& a, const test3_s& b)  {
  }
}
