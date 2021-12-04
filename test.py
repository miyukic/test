#!/usr/bin/python3

class A:
    pass


def main():
    #print(A.__bases__)
    #a = A()
    print(type(f).__bases__)
    func = f()
    func()
    func()
    func()


def f():
    x = []

    def g():
        x.append(1)
        print(x)
    return g


if __name__ == "__main__":
    main()
