using System;
using System.Collections.Generic;

namespace KnapSack
{
    class RecursiveSolver : IKnapSackSolver
    {
		int[] weights, values;
		int size;
		int recursionCalls;
		IEnumerable<int> objectsIncluded;

		public IEnumerable<int> ObjectsIncluded { get => objectsIncluded; }
		public int Complexity { get => recursionCalls; }

        public int SIZE { get => size; }

        public int[] Values { get => values; }

        public int[] Weights { get => weights; }

		public int Solution { get; }

		public RecursiveSolver(int[] weights, int[] values)
        {
			if (weights.Length != values.Length)
				throw new ArgumentException("Lengths of arrays should be equals");
			size = weights.Length;
			if(size > 64)
				throw new ArgumentException("Lengths of arrays should be less as 64");
			this.weights = weights;
			this.values = values;
        }

		public int SolveKnapSack(int W)
        {
            var ret = KnapSack(0, W, 0);
            List<int> list = FlattenMask(ret.mask);
            objectsIncluded = list;
            return ret.val;
        }

        private List<int> FlattenMask(ulong mask)
        {
            var list = new List<int>(SIZE);
            for (int i = 0; i < SIZE; ++i)
            {
                if ((mask & 0x1) != 0)
                    list.Add(i);
                mask = mask >> 1;
            }

            return list;
        }

        // Returns the maximum valuesue that can
        // be put in a knapsack of capacity W
        public (int val, ulong mask) KnapSack(ulong mask, int W, int n)
		{
			// Base Case
			if (n == SIZE || W == 0)
				return (0, mask);

			recursionCalls++;

			// If weight of the nth item is
			// more than Knapsack capacity W,
			// then this item cannot be
			// included in the optimal solution
			if (weights[n] > W)
			{
				return KnapSack(mask, W, n + 1);
			}

			// Return the maximum of two cases:
			// (1) nth item included
			// (2) not included
			else
			{
				ulong newMask = mask | ((ulong)0x1 << n);
				var val1 = KnapSack(newMask, W - weights[n], n + 1);
				var val2 = KnapSack(mask, W, n + 1);
				if (values[n] + val1.val > val2.val)
				{
					return (values[n] + val1.val, val1.mask); ;
				}
				else
				{
					return val2;
				}
			}
		}
	}
}
