using System;
using System.Threading.Tasks;
using System.Threading;

namespace Miyuki.Test {
class Program {
    public static async Task<string> HevyMethod() {
        Console.WriteLine("HevyMethod開始");
        await Task.Run(() => Thread.Sleep(1000));
        return "Hello 1000msが経過しました";
    }

    public static async Task<string> MyAsyncMethod1() {
        string result = await HevyMethod();
        Console.WriteLine("MyAsyncMethod1");
        return result;
    }

    public static async Task<string> MyAsyncMethod2() {
        Thread.Sleep(1000);
        Console.Write("出てくる？");
        string result = await MyAsyncMethod1();
        Console.WriteLine("MyAsyncMethod2" + result);
        return result;
    }

    public static async Task Main(string[] args) {
        MyAsyncMethod2();
    }
}
}
