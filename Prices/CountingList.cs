using System;
using System.Collections;
using System.Collections.Generic;

namespace Prices
{
    public class CountingList<T> : IList<T>
    {
        private IList<T> data;

        public CountingList(int capacity)
        {
            data = new List<T>(capacity);
            for (int i = 0; i < capacity; ++i)
            {
                data.Add(default(T));
            }
        }

        public long GetCount { get; set; }

        public long SetCount { get; set; }

        public T this[int index]
        {
            get
            {
                ++GetCount;
                return data[index];
            }

            set
            {
                ++SetCount;
                data[index] = value;
            }
        }

        public int Count
        {
            get
            {
                return data.Count;
            }
        }

        public bool IsReadOnly
        {
            get
            {
                return false;
            }
        }

        public void Add(T item)
        {
            data.Add(item);
        }

        public void Clear()
        {
            data.Clear();
        }

        public bool Contains(T item)
        {
            return data.Contains(item);
        }

        public void CopyTo(T[] array, int arrayIndex)
        {
            data.CopyTo(array, arrayIndex);
        }

        public IEnumerator<T> GetEnumerator()
        {
            return data.GetEnumerator();
        }

        public int IndexOf(T item)
        {
            return data.IndexOf(item);
        }

        public void Insert(int index, T item)
        {
            data.Insert(index, item);
        }

        public bool Remove(T item)
        {
            return data.Remove(item);
        }

        public void RemoveAt(int index)
        {
            data.RemoveAt(index);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return data.GetEnumerator();
        }
    }
}
