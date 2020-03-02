using System;
using System.Collections;

namespace PnP.Collections
{
    public class HashSet<T> where T : IComparable<T>
    {
        const double FillFactor = 0.7;
        BitArray used;
        T[] keys;
        int size;
        int probingCount;
        int probingSeed;

        public HashSet(int capacity)
        {
            size = (int)(capacity / FillFactor + 0.5);
            used = new BitArray(size);
            keys = new T[size];
        }

        public bool Add(T key)
        {
            var foundRes = FindKey(key);
            bool found = foundRes.Item1;
            if (!found)
            {
                var pos = foundRes.Item2;
                used[pos] = true;
                keys[pos] = key;
            }
            return found;
        }

        public bool Remove(T key)
        {
            var foundRes = FindKey(key);
            bool found = foundRes.Item1;
            if (found)
            {
                var pos = foundRes.Item2;
                used[pos] = false;
            }
            return found;
        }

        public bool Contains(T key)
        {
            var found = FindKey(key);
            return found.Item1;
        }

        /// <summary>
        /// Quadratic probing
        /// </summary>
        /// <param name="pos"></param>
        /// <returns></returns>
        private int Probing(int pos)
        {
            probingSeed++;
            return (pos + probingSeed * probingSeed) % size;
        }

        private void InitProbing()
        {
            probingSeed = 0;
        }

        private Tuple<bool, int> FindKey(T item)
        {
            int pos = item.GetHashCode() % size;
            InitProbing();
            while (used[pos] && keys[pos].CompareTo(item) != 0)
            {
                pos = Probing(pos);
            }
            probingCount += probingSeed;
            bool found = used[pos] && keys[pos].CompareTo(item) == 0;
            return new Tuple<bool, int>(found, pos);
        }
    }
}
