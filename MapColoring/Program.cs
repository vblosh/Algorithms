using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapRepaint
{
    enum Color
    {
        None = 0,
        Red, 
        Blue,
        Green,
        Yellow
    }
    class Program
    {
        static Node[] graph;
        static Color[] colors = { Color.Red, Color.Blue/*, Color.Green, Color.Yellow*/ };

        void InitGraph()
        {
            graph = new Node[6];
            graph[0] = new Node("0");
            graph[1] = new Node("1");
            graph[2] = new Node("2");
            graph[3] = new Node("3");
            graph[4] = new Node("4");
            graph[5] = new Node("5");
            graph[0].Neighbors = new int[] { 1, 2, 4, 5 };
            graph[1].Neighbors = new int[] { 2, 3, 5, 0 };
            graph[2].Neighbors = new int[] { 0, 1, 3, 4 };
            graph[3].Neighbors = new int[] { 1, 2, 4, 5 };
            graph[4].Neighbors = new int[] { 0, 2, 3, 5 };
            graph[5].Neighbors = new int[] { 0, 1, 3, 4 };
        }

        bool IsColorPossible(Node[] graph, int node, Color color)
        {
            foreach (var neighbor in graph[node].Neighbors)
            {
                if (graph[neighbor].Color == color)
                    return false;
            }
            return true;
        }

        bool TryNextNode(Node[] graph, int node, Color[] colors)
        {
            bool success = false;
            foreach(var color in colors)
            {
                if(IsColorPossible(graph, node, color))
                {
                    graph[node].Color = color;
                    success = true;
                    foreach(var neighbor in graph[node].Neighbors)
                    {
                        if (graph[neighbor].Color == Color.None)
                        {
                            success &= TryNextNode(graph, neighbor, colors);
                        }
                    }
                    if (success)
                        return true;
                    else
                        graph[node].Color = Color.None;
                }
            }
            return success;
        }

        static void Main(string[] args)
        {
            Program prog = new Program();
            prog.InitGraph();
            if(prog.TryNextNode(graph, 0, colors))
            {
                Console.WriteLine("Colored successfully");
                for (int node = 0; node < graph.Length; ++node)
                {
                    Console.WriteLine($"Node[{node}].Color={graph[node].Color.ToString()}");
                }
            }
            else
            {
                Console.WriteLine("It is not possible to color map");
            }
        }
    }
}
