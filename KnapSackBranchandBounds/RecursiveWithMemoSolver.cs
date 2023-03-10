using System;
using System.Collections.Generic;

namespace KnapSack
{
	class RecursiveWithMemoSolver : IKnapSackSolver
	{
		int[] weights, values;
		int size;
		int recursionCalls;
		bool[] objectsInculed;
		Dictionary<(int, int), int> memo;
		int[] objectsIncluded = new int[1];

		public IEnumerable<int> ObjectsIncluded { get => objectsIncluded; }
		public int Complexity { get => recursionCalls; }

		public int SIZE { get => size; }

		public int[] Values { get => values; }

		public int[] Weights { get => weights; }

		public int Solution { get; }

		public RecursiveWithMemoSolver(int[] weights, int[] values, int n)
		{
			this.weights = weights;
			this.values = values;
			size = n;
			objectsInculed = new bool[SIZE];
			memo = new Dictionary<(int, int), int>();
		}

		public int SolveKnapSack(int W)
		{
			return KnapSack(W, 0);
		}

		// Returns the maximum valuesue that can
		// be put in a knapsack of capacity W
		public int KnapSack(int W, int n)
		{
			int val;
			if (memo.TryGetValue((W, n), out val))
				return val;

			if (n == SIZE || W == 0)
				return 0;

			recursionCalls++;
			// Base Case

			// If weight of the nth item is
			// more than Knapsack capacity W,
			// then this item cannot be
			// included in the optimal solution
			if (weights[n] > W)
			{
				return KnapSack(W, n + 1);
			}

			// Return the maximum of two cases:
			// (1) nth item included
			// (2) not included
			else
			{
				int val1 = values[n] + KnapSack(W - weights[n], n + 1);
				int val2 = KnapSack(W, n + 1);
				if (val1 > val2)
				{
					memo[(W, n)] = val1;
					return val1;
				}
				else
				{
					memo[(W, n)] = val2;
					return val2;
				}
			}
		}
	}
}
