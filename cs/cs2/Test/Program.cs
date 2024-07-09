using System;
using Microsoft.Win32.SafeHandles;

class Program {

    public static void Main(string[] args) {
        
        Func<double, double> f = (x) => Math.Pow(x, 2) + 2 * x;
        for (uint i = 0; i < 11; ++i) {
            Console.WriteLine(f((double)i));
        }
    }
}
