#!/usr/bin/python3

def main():
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
