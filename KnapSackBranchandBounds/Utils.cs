using System.Collections.Generic;

namespace KnapSack
{
    public static class Utils
    {
        public static List<int> FlattenMask(this ulong mask)
        {
            var list = new List<int>();
            for (int i = 0; i < 64; ++i)
            {
                if ((mask & 0x1) != 0)
                    list.Add(i);
                mask = mask >> 1;
            }

            return list;
        }

    }
}
