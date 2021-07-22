using System.Collections;
using System.Collections.Generic;

namespace KnapSack
{
    interface IKnapSackSolver
    {
		public IEnumerable<int> ObjectsIncluded { get; }
		public int Complexity { get; }

		public int SIZE { get; }

		public int[] Values { get; }

		public int[] Weights { get; }

		// Returns the maximum valuesue that can
		// be put in a knapsack of capacity W
		public int SolveKnapSack(int W);

	}
}
