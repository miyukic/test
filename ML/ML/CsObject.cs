using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Myk {
    public struct CsObject {
        public int x;
        public int y;
    }

    [StructLayout(LayoutKind.Sequential)]    // メンバーは定義順に格納される
    public struct Info {
        [MarshalAs(UnmanagedType.I4)]        // Signed int(4Byte)で格納（属性無くても大丈夫です）
        public int index;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]    // char[128]で格納
        public string name;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 50)]    // int[50]で格納
        public int[] statuses;
        // ↑bool, byte, char, short, int, long, sbyte, ushort,
        // uint, ulong, float, double配列の場合は属性を付けずに以下のようにしても良い
        // この場合は配列のインスタンスを作成する必要は無い。→これはunsafeブロック中でしか使えないらしい・・・
        // public fixed int statuses[50];
    }
    //publiv struct CsMatrixObject {
    //    int y;
    //}
}
