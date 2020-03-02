using System;
using System.Collections;

namespace PnP.Collections
{
    public class HashTable<T, V> where T : IComparable<T>
    {
        const double FillFactor = 0.7;
        BitArray used;
        T[] keys;
        V[] items;
        int size;
        int probingCount;
        int probingSeed;

        public HashTable(int capacity)
        {
            size = (int)(capacity / FillFactor + 0.5);
            used = new BitArray(size);
            keys = new T[size];
            items = new V[size];
        }

        public bool Add(T key, V item)
        {
            var foundRes = FindKey(key);
            bool found = foundRes.Item1;
            var pos = foundRes.Item2;
            if (!found)
            {
                used[pos] = true;
                keys[pos] = key;
                items[pos] = item;
            }
            else
            {
                items[pos] = item;
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
            var findRes = FindKey(key);
            return findRes.Item1;
        }

        public V Get(T key, V item = default(V))
        {
            var foundRes = FindKey(key);
            bool found = foundRes.Item1;
            if (found)
            {
                var pos = foundRes.Item2;
                item = items[pos];
            }
            return item;
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
