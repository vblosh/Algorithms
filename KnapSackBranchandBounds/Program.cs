/* A Naive recursive implementation of
0-1 Knapsack problem */
using System;
namespace KnapSack
{
	static class Helper
    {
		public static int max(int a, int b)
		{
			return (a > b) ? a : b;
		}
    }

	class Program
	{
		static void PrintSolution(IKnapSackSolver solver1, int weight, int solution)
        {
			Console.WriteLine($"Weght={weight}, Solution={solution}, complexity={solver1.Complexity}");
			for (int i = 0; i < solver1.SIZE; i++)
			{
				if (solver1.ObjectsIncluded[i])
				{
					Console.WriteLine("Item[{0,2}](value={1,3}, weght={2,3})", i, solver1.Values[i], solver1.Weights[i]);
				}
			}
		}
		// Driver code
		public static void Main()
		{
			int[] val = new int[] { 60, 100, 120, 100, 200, 10, 25, 35, 5, 1 };
			int[] wt = new int[] { 1, 2, 3, 1, 4, 1, 2, 2, 3, 4 };
			int W = 6;
			int N = 10;
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
