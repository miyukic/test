
Func<int, Func<int, int>> True = x => y => x;

//チャーチ数
Func<Func<int, int>, int>> One = f => x => f(x); 

int Evaluate(Func<Func<int, int>, int> f) {
    return f((int x) => x + 1)(0);
}

Evaluate(One);

//int One(Func<int, int> f) { 
//    return delegate(x) {
//        f(x);
//    }; 
//}


Console.WriteLine(True(1)(2));

