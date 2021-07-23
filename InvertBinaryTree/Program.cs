using System;
using System.Collections.Generic;
using System.Linq;

namespace InvertBinaryTree
{
    class Node
    {
        public Node(int data) { Data = data; }
        public int Data { get; set; }
        public Node Left, Right;
    }


    class Program
    {
        Node CreateBalancedBinaryTree(int[] initData)
        {
            Array.Sort(initData);
            return MakeSubTree(initData, 0, initData.Length - 1);
        }

        Node MakeSubTree(int[] data, int lbound, int rbound)
        {
            if (lbound > rbound) return null;

            int mid = (lbound + rbound) / 2;
            Node root = new Node(data[mid]);
            root.Left = MakeSubTree(data, lbound, mid - 1);
            root.Right = MakeSubTree(data, mid + 1, rbound);
            return root;
        }

        enum ActionOrder
        {
            RootLeftRight,
            LeftRootRight,
            LeftRightRoot
        }

        void DepthFirstSearch(Node node, Action<Node, int> action, int level, ActionOrder actionOrder)
        {
            if (node == null) return;

            switch(actionOrder)
            {
                case ActionOrder.RootLeftRight:
                    action(node, level);
                    DepthFirstSearch(node.Left, action, level + 1, actionOrder);
                    DepthFirstSearch(node.Right, action, level + 1, actionOrder);
                    break;
                case ActionOrder.LeftRootRight:
                    DepthFirstSearch(node.Left, action, level + 1, actionOrder);
                    action(node, level);
                    DepthFirstSearch(node.Right, action, level + 1, actionOrder);
                    break;
                case ActionOrder.LeftRightRoot:
                    DepthFirstSearch(node.Left, action, level + 1, actionOrder);
                    DepthFirstSearch(node.Right, action, level + 1, actionOrder);
                    action(node, level);
                    break;
            }
        }

        void PrintNode(Node node, int level)
        {
            for (int i = 0; i < level; i++)
            {
                Console.Write('\t');
            }
            Console.WriteLine(node.Data);
        }

        void PrintTree(Node root)
        {
            DepthFirstSearch(root, PrintNode, 0, ActionOrder.LeftRootRight);
        }

        public static void Swap<T>(ref T lhs, ref T rhs)
        {
            T temp = lhs;
            lhs = rhs;
            rhs = temp;
        }

        void InvertBinaryTree(Node root)
        {
            DepthFirstSearch(root, (node, level) => Swap(ref node.Left, ref node.Right), 0, ActionOrder.LeftRightRoot);
        }

        static void Main(string[] args)
        {
            Program prog = new Program();
            int[] data = { 3, 7, 2, 4, 1, 6, 8, 9, 5 };
            Node root = prog.CreateBalancedBinaryTree(data);
            prog.PrintTree(root);
            prog.InvertBinaryTree(root);
            prog.PrintTree(root);
        }
    }
}
