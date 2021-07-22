/* A Naive recursive implementation of
0-1 Knapsack problem */
using System;
using System.Linq;
using System.Collections;
using System.Diagnostics;

namespace KnapSack
{
    class Program
    {
        static void PrintSolution(IKnapSackSolver solver1, int weight, int solution)
        {
            Console.WriteLine($"Weght={weight}, Solution={solution}, complexity={solver1.Complexity}");
            foreach (int i in solver1.ObjectsIncluded)
            {
                Console.WriteLine("Item[{0,2}](value={1,3}, weght={2,3})", i, solver1.Values[i], solver1.Weights[i]);
            }
        }

        public static bool CheckBitArraysEquals(BitArray lhs, BitArray rhs)
        {
            if (lhs.Count != rhs.Count) return false;
            for (int i = 0; i < lhs.Count; i++)
            {
                if (lhs[i] != rhs[i])
                    return false;
            }
            return true;
        }

        // Driver code
        public static void Main()
        {
            int[] val = new int[] { 10, 25, 35, 5, 1, 60, 100, 120, 100, 200 };
            int[] wt = new int[] { 1, 2, 3, 1, 4, 1, 2, 2, 3, 4 };
            int W = 10;
            int N = 10;
            /*			for (int j = 1; j <= 10; j++)
                        {
                            for (int i = 1; i <= 10; i++)
                            {
                                W = i;
                                N = j;
                                IKnapSackSolver solver1 = new RecursiveSolver(wt, val, N);
                                int solution1 = solver1.SolveKnapSack(W);

                                IKnapSackSolver solver2 = new RecursiveWithMemoSolver(wt, val, N);
                                int solution2 = solver2.SolveKnapSack(W);
                                Debug.Assert(solution1 == solution2);
                                Debug.Assert(CheckBitArraysEquals(solver1.ObjectsIncluded, solver2.ObjectsIncluded));
                            }
                        }
            */
            IKnapSackSolver solver1 = new RecursiveSolver(wt, val, N);
            int solution1 = solver1.SolveKnapSack(W);
            PrintSolution(solver1, W, solution1);

            IKnapSackSolver solver2 = new RecursiveWithMemoSolver(wt, val, N);
            int solution2 = solver2.SolveKnapSack(W);
            PrintSolution(solver2, W, solution2);

            IKnapSackSolver solver3 = new TableSolver(wt, val, N);
            int solution3 = solver3.SolveKnapSack(W);
            PrintSolution(solver3, W, solution3);
        }
    }
}
