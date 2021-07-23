using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LongestSequence
{
    class Program
    {
        static bool[] input = { false, true, false, true, true, true };

        enum State
        {
            SkipZero = 0,
            CountOne,
            End
        }

        static int maxSeq = 0;

        static void GetMax(int seqLen)
        {
            maxSeq = Math.Max(maxSeq, seqLen);
        }

        static void OutputResult()
        {
            Console.WriteLine($"Maximal one's sequence is {maxSeq} lang");
        }

        static void Main1(string[] args)
        {
            int index = 0;
            State state = State.SkipZero;
            // input
            bool current = false;
            bool end = false;

            int seqLen = 0;
            while (state != State.End)
            {
                end = index == input.Length;
                if (!end) current = input[index++];

                switch (state)
                {
                    case State.SkipZero:
                        {
                            if (end)
                            {
                                OutputResult();
                                state = State.End;
                            }
                            else if (current)
                            {
                                seqLen = 1;
                                state = State.CountOne;
                            }
                        }
                        break;
                    case State.CountOne:
                        {
                            if (end)
                            {
                                GetMax(seqLen);
                                OutputResult();
                                state = State.End;
                            }
                            else if (current)
                            {
                                ++seqLen;
                            }
                            else
                            {
                                GetMax(seqLen);
                                state = State.SkipZero;
                            }
                        }
                        break;
                }
            }
        }


        static void Main2(string[] args)
        {
            int index = 0;
            int seqLen = 0;
            while (index < input.Length)
            {
                // skip zeros
                while (index < input.Length && input[index] == false) ++index;

                seqLen = 0;
                // count ones
                while (index < input.Length && input[index] == true)
                {
                    ++seqLen;
                    ++index;
                }
                GetMax(seqLen);
            }
            OutputResult();
        }
    }
}
