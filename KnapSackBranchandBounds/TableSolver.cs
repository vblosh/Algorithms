using System;
using System.Collections.Generic;

namespace KnapSack
{
    class TableSolver : IKnapSackSolver
    {
        struct TableCell
        {
            public int Value;
            public ulong Objects;
        };
        int[] weights, values;
        int size;
        int complexity;
        TableCell[,] table;
        IEnumerable<int> objectsInculed;

        public IEnumerable<int> ObjectsIncluded { get => objectsInculed; }
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
            if (size > 64)
                throw new ArgumentException("Lengths of arrays should be less as 64");
        }

        TableCell Max(TableCell lhs, TableCell rhs)
        {
            return lhs.Value > rhs.Value ? lhs : rhs;
        }

        // Returns the maximum valuesue that can
        // be put in a knapsack of capacity W
        public int SolveKnapSack(int W)
        {
            table = new TableCell[SIZE + 1, W + 1];

            for (int i = 1; i <= SIZE; i++)
            {
                for (int j = 1; j <= W; j++)
                {
                    TableCell val = new TableCell();
                    int itemIdx = i - 1;
                    if (weights[itemIdx] <= j)
                    {
                        var cellBefore = table[itemIdx, j - weights[itemIdx]];
                        val.Value = values[itemIdx] + cellBefore.Value;
                        val.Objects = cellBefore.Objects | ((ulong)0x1 << itemIdx);
                   }
                    table[i, j] = Max(table[itemIdx, j], val);
                }
            }
            complexity = SIZE * W;

            objectsInculed = table[SIZE, W].Objects.FlattenMask();
            return table[SIZE, W].Value;
        }
    }
}
