using System;
using System.Threading.Tasks;

namespace BacktrackingKnightsTour
{
    class KnightsTour
    {
        const int SIZE = 6;
        const int NUM_MOVE = 8;
        struct MoveShift
        {
            public MoveShift(int dx, int dy)
            {
                this.dx = dx;
                this.dy = dy;
            }
            public int dx, dy;
        }

        MoveShift[] moveShifts = new MoveShift[NUM_MOVE] {
            new MoveShift( -1, -2 ), new MoveShift(1, -2),
            new MoveShift( 2, -1 ), new MoveShift(2, 1),
            new MoveShift( -1, 2 ), new MoveShift(1, 2),
            new MoveShift( -2, -1 ), new MoveShift(-2, 1),
        };

        int[,] board = new int[SIZE, SIZE];

        bool Accept(int x, int y)
        {
            return x >= 0 && y >= 0 && x < SIZE && y < SIZE && board[x, y] == 0;
        }

        bool Backtrack(int x, int y, int n)
        {
            for (int i = 0; i < NUM_MOVE; i++)
            {
                int newX = x + moveShifts[i].dx;
                int newY = y + moveShifts[i].dy;
                if (Accept(newX, newY))
                {
                    board[newX, newY] = n;
                    if (n == SIZE * SIZE)
                        return true;    // solution found

                    if (Backtrack(newX, newY, n + 1))
                        return true;

                    board[newX, newY] = 0;
                }
            }
            return false;
        }

        void PrintBoard()
        {
            for (int y = 0; y < SIZE; y++)
            {
                for (int x = 0; x < SIZE; x++)
                {
                    Console.Write("{0,4}", board[x, y]);
                }
                Console.WriteLine();
            }
        }

        static void Main(string[] args)
        {
            // because of symmetry we canrun it only for left, top part of the board
            object sync = new object();

            Parallel.For(0, SIZE / 2,
                (x) => Parallel.For(0, SIZE / 2, (y) => {
                    KnightsTour tour = new KnightsTour();
                    if (tour.Backtrack(x, y, 1))
                        lock (sync)
                        {
                            Console.WriteLine($"Solution for x={x}, y={y}:");
                            tour.PrintBoard();
                            Console.WriteLine();
                        }
                    else
                        lock (sync)
                            Console.WriteLine($"Solution for x={x}, y={y} not found!");
                }
                ));

            //KnightsTour tour = new KnightsTour();
            //if (tour.Backtrack(1, 2, 1))
            //    tour.PrintBoard();
            //else
            //    Console.WriteLine("Solution not found!");
        }
    }
}
