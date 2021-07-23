using System;
using System.Diagnostics;

namespace Fibbonacci
{
    class Program
    {
        public static ulong Fib(uint  n)
        {
            if (n == 1 || n == 2)
                return 1ul;
            else
                return Fib(n - 1) + Fib(n - 2);
        }

        static ulong[] memo = new ulong[128];

        static Program()
        {
            memo[0] = 0;
            memo[1] = memo[2] = 1;

            fibcalc[0] = 0;
            fibcalc[1] = fibcalc[2] = 1;

        }

        public static ulong FibMemo(uint n)
        {
            if (memo[n] == 0)
                memo[n] = FibMemo(n - 1) + FibMemo(n - 2);

            return memo[n];
        }

        static ulong[] fibcalc = new ulong[128];
        public static ulong FibCalc(uint n)
        {
            for (int i = 3; i <= n; ++i)
            {
                fibcalc[i] = fibcalc[i - 1] + fibcalc[i - 2];
            }

            return fibcalc[n];
        }


        static void Main(string[] args)
        {
            uint n = 40;
            Stopwatch sw = new Stopwatch();
            ulong res;
            sw.Start();
            res = Fib(n);
            sw.Stop();
            var elapsed1 = sw.ElapsedTicks;
            Console.WriteLine($"Elapsed={elapsed1} ticks");
            Console.WriteLine($"fib({n})={res}");


            sw.Restart();
            res = FibMemo(n);
            sw.Stop();
            var elapsed2 = sw.ElapsedTicks;
            var times = (double)elapsed1 / elapsed2;
            Console.WriteLine($"Elapsed={elapsed2} ticks, {times} times faster");
            Console.WriteLine($"fib({n})={res}");

            sw.Restart();
            res = FibCalc(n);
            sw.Stop();
            var elapsed3 = sw.ElapsedTicks;
            var times2 = (double)elapsed1 / elapsed3;
            Console.WriteLine($"Elapsed={elapsed3} ticks, {times2} times faster");
            Console.WriteLine($"fib({n})={res}");
            Console.ReadKey();
        }
    }
}
