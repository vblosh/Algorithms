using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using PnP.Collections;
using System.IO;

namespace LinqIntersection
{
    class Program
    {
        const int N = 1000000;
        int[] set1, set2;

        void PrepareData()
        {
            set1 = new int[N];
            set2 = new int[N];
            Random rnd1 = new Random(1234567);
            Random rnd2 = new Random(7654321);
            for (int i = 0; i < N; i++)
            {
                set1[i] = rnd1.Next();
                set2[i] = rnd2.Next();
            }
        }

        void SaveArray(string fileName, int[] arr)
        {
            using (StreamWriter writer = new StreamWriter(fileName))
            {
                foreach (var item in arr)
                {
                    writer.WriteLine(item);
                }
            }
        }

        int CountIntersect()
        {
            int res = (from int a in set1 join int b in set2 on a equals b select 1).Count();
            return res;
        }

        int CountIntersectHashset()
        {
            System.Collections.Generic.HashSet<int> hashTable = new System.Collections.Generic.HashSet<int>(set1);
            var qry = hashTable.Intersect(set2);
            return qry.Count();
        }

        int CountIntersectHashTable()
        {
            PnP.Collections.HashTable<int, int> hashTable = new PnP.Collections.HashTable<int, int>(set1.Length);
            for (int i = 0; i < set1.Length; i++)
            {
                hashTable.Add(set1[i], i);
            }

            int cnt = 0;
            for (int i = 0; i < N; i++)
            {
                if (hashTable.Contains(set2[i]))
                    cnt++;
            }
            return cnt;
        }

        static void Main(string[] args)
        {
            Program pr = new Program();
            pr.PrepareData();
            //pr.SaveArray("set1.txt", pr.set1);
            //pr.SaveArray("set2.txt", pr.set2);

            Stopwatch sw = new Stopwatch();
            int n;
            sw.Restart();
            n = pr.CountIntersectHashTable();
            sw.Stop();
            Console.WriteLine($"HashTable Intersect={n}, Elapsed {sw.ElapsedTicks} ticks");

            sw.Restart();
            n = pr.CountIntersectHashset();
            sw.Stop();
            Console.WriteLine($"Hashset Intersect={n}, Elapsed {sw.ElapsedTicks} ticks");

            sw.Restart();
            n = pr.CountIntersect();
            sw.Stop();
            Console.WriteLine($"Linq Intersect={n}, Elapsed {sw.ElapsedTicks} ticks");
        }
    }
}
