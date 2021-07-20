namespace KnapSack
{
    class TableSolver : IKnapSackSolver
    {
        int[] weights, values;
        int size;
        int complexity;
        bool[] objectsInculed;
        int[,] table;

        public bool[] ObjectsIncluded { get => objectsInculed; }
        public int Complexity { get => complexity; }

        public int SIZE { get => size; }

        public int[] Values { get => values; }

        public int[] Weights { get => weights; }

        public int Solution { get; }

        public TableSolver(int[] weights, int[] values, int n)
        {
            this.weights = weights;
            this.values = values;
            size = n;
            objectsInculed = new bool[SIZE];
        }

        // Returns the maximum valuesue that can
        // be put in a knapsack of capacity W
        public int SolveKnapSack(int W)
        {
            table = new int[SIZE + 1, W + 1];

            for (int i = 1; i <= SIZE; i++)
            {
                for (int j = 1; j <= W; j++)
                {
                    int val = 0;
                    if (weights[i - 1] <= j)
                    {
                        val = values[i - 1] + table[i - 1, j - weights[i - 1]];
                    }
                    table[i, j] = Helper.max(table[i - 1, j], val);
                }
            }
            complexity = SIZE * W;

            return table[SIZE, W];
        }
    }
}
