#!/usr/bin/python3

class A:
    a = 0
    b = "A Class です"

class B(A):
    pass

print("__dict__keys() = ", B.__dict__.keys())
print("dir() = ", dir(B))
#class A:

#    def f(self):
#        print("変更される前の関数fです")


#    @staticmethod
#    def g():
#        print("変更される前の関数gです")


#    @classmethod
#    def h(cls):
#        print("変更される前の関数hです")


#def foo(self):
#    print("変更された後の関数f")


#def main():
#    a = A()
#    a.f = foo
#    a.f()


#if __name__ == "__main__":
#    main()
