using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DijkstraAlgo
{
    internal class Edge
    {
        public Edge(int node, int costs)
        {
            Node = node;
            Costs = costs;
        }
        public int Node;
        public int Costs;
    }

    internal class Node
    {
        public Node(string id, Edge[] edges) { Id = id; Edges = edges; }
        public string Id { get; set; }
        public Edge[] Edges { get; set; }
        public bool Visited { get; set; } = false;
        public int Weight { get; set; } = int.MaxValue;
        public int Parent { get; set; } = -1;
    }
}
