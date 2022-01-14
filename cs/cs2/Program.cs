// See https://aka.ms/new-console-template for more information
using System;
//using System.Linq.Expressions;
using System.Numerics;
using System.Timers;


partial class Program {

    public static async Task Main(String[] args) {
        var a = Program.CalcCall(40);
        Console.WriteLine(a);
    }


    public static async Task<BigInteger> CalvCall(int n) {
        return await Calc(n);
    }


    public static BigInteger Calc(int n) {
        if (n == 0) {
            return new BigInteger(0);
        }

        if (n == 1) {
            return Calc(0) + new BigInteger(1);
        }

        return Calc(n - 1) + Calc(n - 2);
    }
}

//class Program {
//    public static void Main() {
//        // 5+7*3
//        Expression body = Expression.Add(Expression.Constant(5),
//                Expression.Multiply(Expression.Constant(7),
//                    Expression.Constant(3)
//                    )
//                );
//
//        Expression<Func<int>> lambda = Expression.Lambda<Func<int>>(body);
//        Func<int> func = lambda.Compile();
//       Console.WriteLine(func());
//    }
//}

