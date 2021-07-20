namespace KnapSack
{
    interface IKnapSackSolver
    {
		public bool[] ObjectsIncluded { get; }
		public int Complexity { get; }

		public int SIZE { get; }

		public int[] Values { get; }

		public int[] Weights { get; }

		// Returns the maximum valuesue that can
		// be put in a knapsack of capacity W
		public int SolveKnapSack(int W);

	}
}
