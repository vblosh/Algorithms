using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;

namespace Prices
{
    class Program
    {
        struct TradeResult
        {
            public double earning;
            public int day1, day2;
        }

        const int NUM_ALG = 3;
        const int SIZE1 = 10000;
        const int SIZE2 = 100000;

        const int ACCESS_SIZE = 1000;

        static void Main(string[] args)
        {
            TimeBenchmark();
            AccessBenchmark();

            Console.ReadLine();
        }

        private static void AccessBenchmark()
        {
            var rnd = new Random(12345678);
            var prices = new CountingList<double>(ACCESS_SIZE);
            for (int i = 0; i < prices.Count; ++i)
            {
                prices[i] = 10.0 * rnd.Next() / int.MaxValue;
            }

            double trade;
            var res = CalcBestTradeBruteForce(prices);
            trade = res.earning;
            Console.WriteLine($"Best deal brute force O(N^2) earning={trade}, operation count={prices.GetCount}");

            prices.GetCount = 0;
            trade = CalcBestTradeDivideConquer1(prices, 0, prices.Count - 1);
            Console.WriteLine($"Best deal devide&conquer O(N*logN) earning={trade}, operation count={prices.GetCount}");

            prices.GetCount = 0;
            var res1 = CalcBestTradeDivideConquer(prices, 0, prices.Count - 1);
            trade = res1.earning;
            Console.WriteLine($"Best deal devide&conquer O(N) earning={trade}, operation count={prices.GetCount}");


            prices.GetCount = 0;
            trade = CalcBestTradeIterative(prices);
            Console.WriteLine($"Best deal iterative O(N) earning={trade}, operation count={prices.GetCount}");

            prices.GetCount = 0;
            trade = CalcBestTradeIterativeKadane(prices);
            Console.WriteLine($"Best deal iterative Kadane O(N) earning={trade}, operation count={prices.GetCount}");
        }

        private static void TimeBenchmark()
        {
            var rnd = new Random(12345678);
            double[] prices = new double[SIZE1];
            for (int i = 0; i < prices.Length; ++i)
            {
                prices[i] = 10.0 * rnd.Next() / int.MaxValue;
            }

            double[] prices1 = new double[SIZE2];
            for (int i = 0; i < prices1.Length; ++i)
            {
                prices1[i] = 100.0 * rnd.Next() / int.MaxValue;
            }
            long tm1, tm2;
            double trade1, trade2;
            Stopwatch sw = new Stopwatch();

            var res = CalcBestTradeBruteForce(prices);
            sw.Start();
            res = CalcBestTradeBruteForce(prices);
            trade1 = res.earning;
            sw.Stop();
            tm1 = sw.ElapsedTicks;

            res = CalcBestTradeBruteForce(prices1);
            sw.Restart();
            res = CalcBestTradeBruteForce(prices1);
            trade2 = res.earning;
            sw.Stop();
            tm2 = sw.ElapsedTicks;
            Console.WriteLine($"Best deal brute force O(N^2) earning={trade1} and {trade2}, elapsed time={tm1} and {tm2}, factor={(double)tm2 / tm1}");

            trade1 = CalcBestTradeDivideConquer1(prices, 0, prices.Length - 1);
            sw.Restart();
            trade1 = CalcBestTradeDivideConquer1(prices, 0, prices.Length - 1);
            sw.Stop();
            tm1 = sw.ElapsedTicks;

            trade2 = CalcBestTradeDivideConquer1(prices1, 0, prices1.Length - 1); ;
            sw.Restart();
            trade2 = CalcBestTradeDivideConquer1(prices1, 0, prices1.Length - 1); ;
            sw.Stop();
            tm2 = sw.ElapsedTicks;
            Console.WriteLine($"Best deal devide&conquer O(N*logN) earning={trade1} and {trade2}, elapsed time={tm1} and {tm2}, factor={(double)tm2 / tm1}");

            trade1 = CalcBestTradeDivideConquer(prices, 0, prices.Length - 1).earning;
            sw.Restart();
            trade1 = CalcBestTradeDivideConquer(prices, 0, prices.Length - 1).earning;
            sw.Stop();
            tm1 = sw.ElapsedTicks;

            trade2 = CalcBestTradeDivideConquer(prices1, 0, prices1.Length - 1).earning;
            sw.Restart();
            trade2 = CalcBestTradeDivideConquer(prices1, 0, prices1.Length - 1).earning;
            sw.Stop();
            tm2 = sw.ElapsedTicks;
            Console.WriteLine($"Best deal devide&conquer O(N) earning={trade1} and {trade2}, elapsed time={tm1} and {tm2}, factor={(double)tm2 / tm1}");

            trade1 = CalcBestTradeIterative(prices);
            sw.Restart();
            trade1 = CalcBestTradeIterative(prices);
            sw.Stop();
            tm1 = sw.ElapsedTicks;

            trade2 = CalcBestTradeIterative(prices1);
            sw.Restart();
            trade2 = CalcBestTradeIterative(prices1);
            sw.Stop();
            tm2 = sw.ElapsedTicks;
            Console.WriteLine($"Best deal iterative O(N) earning={trade1} and {trade2}, elapsed time={tm1} and {tm2}, factor={(double)tm2 / tm1}");

            trade1 = CalcBestTradeIterativeKadane(prices);
            sw.Restart();
            trade1 = CalcBestTradeIterativeKadane(prices);
            sw.Stop();
            tm1 = sw.ElapsedTicks;

            trade2 = CalcBestTradeIterativeKadane(prices1);
            sw.Restart();
            trade2 = CalcBestTradeIterativeKadane(prices1);
            sw.Stop();
            tm2 = sw.ElapsedTicks;
            Console.WriteLine($"Best deal iterative Kadane algorithm O(N) earning={trade1} and {trade2}, elapsed time={tm1} and {tm2}, factor={(double)tm2 / tm1}");
        }

        static TradeResult CalcBestTradeBruteForce(IList<double> prices)
        {
            var bestTrade = new TradeResult();
            bestTrade.earning = double.MinValue;
            for (int i = 0; i < prices.Count; ++i)
            {
                for (int j = i + 1; j < prices.Count; ++j)
                {
                    double current = prices[j] - prices[i];
                    if (current > bestTrade.earning)
                    {
                        bestTrade.day1 = i;
                        bestTrade.day2 = j;
                        bestTrade.earning = current;
                    }
                }
            }
            return bestTrade;
        }

        static double Min(IList<double> arr, int lidx, int ridx)
        {
            double result = arr[lidx];
            for (int i = lidx + 1; i <= ridx; ++i)
            {
                if (result > arr[i])
                    result = arr[i];
            }
            return result;
        }

        static double Max(IList<double> arr, int lidx, int ridx)
        {
            double result = arr[lidx];
            for (int i = lidx + 1; i <= ridx; ++i)
            {
                if (result < arr[i])
                    result = arr[i];
            }
            return result;
        }

        static double CalcBestTradeDivideConquer1(IList<double> prices, int lidx, int ridx)
        {
            if (lidx == ridx)
            {
                return 0.0;
            }
            double[] ear = new double[3];
            ear[0] = CalcBestTradeDivideConquer1(prices, lidx, (lidx + ridx) / 2);
            ear[1] = CalcBestTradeDivideConquer1(prices, (lidx + ridx) / 2 + 1, ridx);
            ear[2] = Max(prices, (lidx + ridx) / 2 + 1, ridx) - Min(prices, lidx, (lidx + ridx) / 2);

            return Max(ear, 0, 2);
        }

        struct Result1
        {
            public double earning;
            public double min, max;
        }

        static Result1 CalcBestTradeDivideConquer(IList<double> prices, int lidx, int ridx)
        {
            if (lidx == ridx)
            {
                double curPrice = prices[lidx];
                return new Result1 { earning = 0.0, min = curPrice, max = curPrice };
            }
            var ear0 = CalcBestTradeDivideConquer(prices, lidx, (lidx + ridx) / 2);
            var ear1 = CalcBestTradeDivideConquer(prices, (lidx + ridx) / 2 + 1, ridx);
            double ear2 = ear1.max - ear0.min;
            double min = ear0.min < ear1.min ? ear0.min : ear1.min;
            double max = ear0.max > ear1.max ? ear0.max : ear1.max;
            double earn = ear0.earning;
            if (earn < ear1.earning)
                earn = ear1.earning;
            if (earn < ear2)
                earn = ear2;

            return new Result1 { earning = earn, min = min, max = max };
        }

        static double CalcBestTradeIterative(IList<double> prices)
        {
            double bestTrade = 0;
            int[] bestBuyDay = new int[prices.Count];
            bestBuyDay[0] = 0;
            for (int i = 1; i < prices.Count; ++i)
            {
                double curPrice = prices[i];
                if (curPrice < prices[bestBuyDay[i - 1]])
                    bestBuyDay[i] = i;
                else
                    bestBuyDay[i] = bestBuyDay[i - 1];

                var trade = curPrice - prices[bestBuyDay[i]];
                if (trade > bestTrade)
                    bestTrade = trade;
            }

            return bestTrade;
        }

        static double CalcBestTradeIterativeKadane(IList<double> prices)
        {
            double bestTrade = 0;
            double minPrice = prices[0];

            for (int i = 1; i < prices.Count; ++i)
            {
                double curPrice = prices[i];
                var trade = curPrice - minPrice;
                if (trade > bestTrade)
                {
                    bestTrade = trade;
                }
                if (curPrice < minPrice)
                {
                    minPrice = curPrice;
                }
            }

            return bestTrade;
        }
    }
}
