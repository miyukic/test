// See https://aka.ms/new-console-template for more information
using System;
using System.Linq.Expressions;

class Program {
    public static void Main() {
        // 5+7*3
        Expression body = Expression.Add(Expression.Constant(5),
                Expression.Multiply(Expression.Constant(7),
                    Expression.Constant(3)
                    )
                );

        Expression<Func<int>> lambda = Expression.Lambda<Func<int>>(body);
        System.Console.WriteLine(lambda.);
    }
}

