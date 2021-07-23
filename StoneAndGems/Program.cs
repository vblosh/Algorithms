using System;
using System.Collections.Generic;

/*
 * Даны две строки строчных латинских символов: строка J и строка S. 
 * Символы, входящие в строку J, — «драгоценности», входящие в строку S — «камни». 
 * Нужно определить, какое количество символов из S одновременно являются «драгоценностями». 
 * Проще говоря, нужно проверить, какое количество символов из S входит в J.
 */
namespace StoneAndGems
{
    class Program
    {
        static string J = "abcc";
        static string S = "system.threading.tasks";
        static HashSet<char> gems = new HashSet<char>(J);
        
        static void Main(string[] args)
        {
            int result = 0;
            foreach (char stone in S)
            {
                if (gems.Contains(stone))
                    ++result;
            }
            Console.WriteLine($"{result} stones are gems");
        }
    }
}
