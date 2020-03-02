using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

class TrieNode
{
    const int NUM_BUCKETS = 26;
    public char Symbol;
    public int Count;
    public TrieNode Parent;
    public TrieNode[] Children;

    public TrieNode(char symbol, TrieNode parent)
    {
        Symbol = symbol;
        Parent = parent;
        Children = new TrieNode[NUM_BUCKETS];
    }

    public override string ToString()
    {
        return string.Format($"Symbol={Symbol}, Parent={Parent.Symbol}, Count={Count}");
    }
}

enum Operation
{
    Add,
    Find,
};

struct OpData
{
    public Operation Operation;
    public string Contact;
};

class Solution
{
    static TrieNode root = null;

    static int Index(char ch)
    {
        return ch - 'a';
    }

    static void Add(string s)
    {
        var res = Find(root, s);
        TrieNode node = res.Item2;
        for (int i = res.Item3; i < s.Length; i++)
        {
            char ch = s[i];
            TrieNode newnode = new TrieNode(ch, node);
            node.Children[Index(ch)] = newnode;
            node = newnode;
        }
        while (node != null)
        {
            node.Count++;
            node = node.Parent;
        }
    }

    public static Tuple<bool, TrieNode, int> Find(TrieNode node, string s)
    {
        for (int i = 0; i < s.Length; i++)
        {
            if (node.Children[Index(s[i])] != null)
            {
                node = node.Children[Index(s[i])];
            }
            else
                return new Tuple<bool, TrieNode, int>(false, node, i);
        }
        return new Tuple<bool, TrieNode, int>(true, node, s.Length);
    }

    static void Main(String[] args)
    {
        root = new TrieNode('■', null);

        int n = Convert.ToInt32(Console.ReadLine());
        OpData[] opData = new OpData[n];
        int numFind = 0;
        for (int i = 0; i < n; i++)
        {
            string[] tokens_op = Console.ReadLine().Split(' ');
            string op = tokens_op[0];
            string contact = tokens_op[1];

            if (op == "add")
            {

                opData[i] = new OpData { Operation = Operation.Add, Contact = contact };
            }
            else if (op == "find")
            {
                numFind++;
                opData[i] = new OpData { Operation = Operation.Find, Contact = contact };
            }
            else
                throw new Exception("wrong operation");
        }

        int[] finds = new int[numFind];

        Stopwatch sw = new Stopwatch();

        sw.Start();
        int idxFind = 0;
        foreach (var oper in opData)
        {
            if (oper.Operation == Operation.Add)
            {
                Add(oper.Contact);
            }
            else if (oper.Operation == Operation.Find)
            {
                var res = Find(root, oper.Contact);
                if (res.Item1)
                {
                    finds[idxFind++] = (res.Item2.Count);
                }
                else
                {
                    finds[idxFind++] = 0;
                }
            }
        }
        sw.Stop();
        Console.WriteLine($"Total {sw.ElapsedMilliseconds}ms");

        foreach (int nf in finds)
        {
            Console.WriteLine(nf);
        }
    }
}