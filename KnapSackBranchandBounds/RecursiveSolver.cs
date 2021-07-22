using System;
using System.Collections.Generic;
using System.Collections;

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

		public RecursiveSolver(int[] weights, int[] values, int n)
        {
			size = n;
			if (weights.Length < size || values.Length < size)
				throw new ArgumentException("Lengths of arrays should be greater as n");
			if(size > 64)
				throw new ArgumentException("Lengths of arrays should be less as 64");
			this.weights = weights;
			this.values = values;
        }

		public int SolveKnapSack(int W)
        {
            var ret = KnapSack(0, W, 0);
            List<int> list = ret.mask.FlattenMask();
            objectsIncluded = list;
            return ret.val;
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

	class RecursiveSolver1 : IKnapSackSolver
	{
		int[] weights, values;
		int size;
		int recursionCalls;
		int[] objectsIncluded;

		public IEnumerable<int> ObjectsIncluded { get => objectsIncluded; }
		public int Complexity { get => recursionCalls; }

		public int SIZE { get => size; }

		public int[] Values { get => values; }

		public int[] Weights { get => weights; }

		public int Solution { get; }

		public RecursiveSolver1(int[] weights, int[] values, int n)
		{
			this.weights = weights;
			this.values = values;
			size = n;
		}

		public int SolveKnapSack(int W)
		{
			var ret = KnapSack(new BitArray(SIZE), W, 0);
			Stack<int> stack = new Stack<int>();
			for (int i = ret.Item2.Length - 1; i >= 0; --i)
			{
				if (ret.Item2[i])
					stack.Push(i);
			}

			objectsIncluded = stack.ToArray();
			return ret.Item1;
		}

		// Returns the maximum valuesue that can
		// be put in a knapsack of capacity W
		public Tuple<int, BitArray> KnapSack(BitArray objs, int W, int n)
		{
			// Base Case
			if (n == SIZE || W == 0)
				return new Tuple<int, BitArray>(0, new BitArray(objs));

			recursionCalls++;

			// If weight of the nth item is
			// more than Knapsack capacity W,
			// then this item cannot be
			// included in the optimal solution
			if (weights[n] > W)
			{
				return KnapSack(new BitArray(objs), W, n + 1);
			}

			// Return the maximum of two cases:
			// (1) nth item included
			// (2) not included
			else
			{
				var newObjs = new BitArray(objs);
				newObjs.Set(n, true);
				var val1 = KnapSack(newObjs, W - weights[n], n + 1);
				var val2 = KnapSack(new BitArray(objs), W, n + 1);
				if (values[n] + val1.Item1 > val2.Item1)
				{
					return new Tuple<int, BitArray>(values[n] + val1.Item1, val1.Item2); ;
				}
				else
				{
					return val2;
				}
			}
		}
	}


}
