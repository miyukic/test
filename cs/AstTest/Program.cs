using System;
using System.Linq.Expressions;

Func<int> f = () => 3 + 5;
//Console.WriteLine("f() = " + f());


Expression<Func<int>> ast = () => 12 + 5;

Func<int> g = ast.Compile();
Console.WriteLine("g() = " + g());
