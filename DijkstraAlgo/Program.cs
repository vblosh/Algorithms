using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DijkstraAlgo
{

    class Program
    {
        static Node[] graph;
        static int[] queue;

        void InitGraph()
        {
            graph = new Node[4];
            graph[0] = new Node("0", new Edge[] { new Edge(1, 6), new Edge(2, 2) });
            graph[1] = new Node("1", new Edge[] { new Edge(0, 6), new Edge(2, 1), new Edge(3, 3) });
            graph[2] = new Node("2", new Edge[] { new Edge(0, 2), new Edge(1, 1), new Edge(3, 5) });
            graph[3] = new Node("3", new Edge[] { new Edge(1, 3), new Edge(2, 5) });
        }

        void Visit(Node[] graph)
        {
            //queue.Min(idx => graph[idx].Weight);
            //foreach(var edge in graph[currentNode].Edges)
            //{
            //    if(graph[edge.Node].Weight > graph[currentNode].Weight + edge.Costs)
            //    {
            //        graph[edge.Node].Weight = graph[currentNode].Weight + edge.Costs;
            //    }
            //    if(!graph[edge.Node].Visited)
            //    {

            //    }
            //}

        }

        static void Main(string[] args)
        {
            Program prog = new Program();
            prog.InitGraph();
            // start Node
            int start = 0;
            graph[start].Weight = 0;
 //           prog.Visit(graph, start);
        }
    }
}
