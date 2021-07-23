using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapRepaint
{

    class Node
    {
        public Node(string name) { Name = name; }
        public string Name { get; set; }
        public Color Color;
        public int[] Neighbors { get; set; }
    }
}
