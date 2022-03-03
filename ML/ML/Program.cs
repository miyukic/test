#if NET6_0
#nullable enable

using System;
using System.Collections.Generic;
using System.Diagnostics;
using Myk.Lib;
using System.Runtime.InteropServices;
using System.Linq;


namespace Myk {
    namespace Util {
#region Experimental Code
        class Seconds {
            int value;
            public Seconds(int v) {
                this.value = v;
            }
            public static implicit operator Minutes(Seconds val) {
                return new Minutes(val.value / 60);
            }

            public static implicit operator Hours(Seconds val) {
                return new Seconds(val.value / 60);
            }
        }
        
        class Minutes {
            int value;
            public Minutes(int v) {
                this.value = v;
            }

            public static implicit operator Hours(Minutes val) {
                return new Hours(val.value / 60);
            }

            public static implicit operator Seconds(Minutes val) {
                return new Seconds(val.value * 60);
            }
        }

        class Hours {
            int value;
            public Hours(int v) {
                this.value = v;
            }

            public static implicit operator Seconds(Hours val) {
                return new Seconds(val.value / 60 / 60);
            }

            public static implicit operator Minutes(Hours val) {
                return new Minutes(val.value / 60);
            }

        }
        #endregion
    }　// .Util namespace end
    namespace Lib {
        #region Matrix
        using ID = System.UInt16;
        using BOOL = System.Int32;
        // C++で実装されたMatrixクラスの薄いラッパークラス
        class CMatrix {
            public uint ROW { get; }
            public uint CUL { get; }
            private ID _id;
            public ID id { get { return _id; } }

            /// <summary>
            /// 行と列(と初期値(value=0.0))を指定して初期化
            /// </summary>
            /// <param name="ROW">行</param>
            /// <param name="CUL">列</param>
            /// <param name="value"></param>
            public CMatrix(uint ROW, uint CUL, double value = 0.0) {
                this.ROW = ROW;
                this.CUL = CUL;
                _id = NativeMethod.createNativeMatrixRCV(ROW, CUL, value);
            }

            /// <summary>
            /// IDと行と列を指定して作成
            /// 存在しないIDを指定するのは禁止(C++側から返ってきたIDのみ指定可能)。
            /// </summary>
            /// <param name="id"></param>
            /// <param name="ROW">行</param>
            /// <param name="CUL">列</param>
            private CMatrix(ID id, uint ROW, uint CUL) {
                this.ROW = ROW;
                this.CUL = CUL;
                _id = id;
            }

            /// <summary>
            /// 配列でCMatrixクラスを初期化するコンストラクタ
            /// </summary>
            /// <param name="array"></param>
            public CMatrix(in double[,] array2) {
                uint row = (uint) array2.GetLength(0);
                uint cul = (uint) array2.GetLength(1);
                double[] array = 
                    //array2.OfType<double>().ToArray();
                    array2.Cast<double>().ToArray();
                //ofType<TResult> Cast<TResult>
                //https://referencesource.microsoft.com/#System.Core/System/Linq/Enumerable.cs,d25cf953c577dcd6
                (IntPtr pInt, uint len) = CreateNativeDoubleArray(array);
                _id = NativeMethod.createNativeMatrixARC(pInt, len, row, cul);
            }

            public bool Print() {
                return NativeMethod.nativeMatrixPrint(_id);
            }

            public static bool operator==(CMatrix lhs, CMatrix rhs) {
                //Console.WriteLine("operator== " + NativeMethod.equals(lhs.id, rhs.id));
                return Convert.ToBoolean(NativeMethod.nativeMatrixEquals(lhs.id, rhs.id));
            }

            public static bool operator!=(CMatrix lhs, CMatrix rhs) {
                return !Convert.ToBoolean(NativeMethod.nativeMatrixEquals(lhs.id, rhs.id));
            }

            /// <summary>
            /// 行列積
            /// </summary>
            /// <param name="lhs"></param>
            /// <param name="rhs"></param>
            /// <returns></returns>
            public static CMatrix Multiply(in CMatrix lhs, in CMatrix rhs) {
                ID newid = NativeMethod.nativeMatrixMultiply(lhs.id, rhs.id);
                CMatrix newMat = new CMatrix(newid, lhs.ROW, rhs.CUL);
                return newMat;
            }


            /// <summary>
            /// 配列からアンマネージド型の配列をメモリ上に生成しそのIntPtrと配列のサイズを返す
            /// IntPtr = void*
            /// </summary>
            /// <param name="array"></param>
            /// <returns></returns>
            private static (System.IntPtr, uint)CreateNativeDoubleArray(double[] array) {
                int length = array.Length;
                // 確保する配列のメモリサイズ（double型 × 長さ）  
                int size = Marshal.SizeOf(typeof(double)) * length;
                // C++に渡す配列のアンマネージドメモリを確保  
                // ※「ptr」は確保したメモリのポインタ  
                System.IntPtr ptr = Marshal.AllocCoTaskMem((int)size);
                // C#の配列をアンマネージドメモリにコピーする  
                Marshal.Copy(array, 0, ptr, length);
                // C++に配列を渡す(ポインタを渡す)  
                return (ptr, (uint) length);
                // アンマネージドのメモリを解放  
                //Marshal.FreeCoTaskMem(ptr);
            }

            //C++の関数
            static class NativeMethod {
                [DllImport("MlLib.dll")]
                public static extern ID createNativeMatrixRCV(uint ROW, uint CUL, double value);

                [DllImport("MlLib.dll")]
                public static extern ID createNativeMatrixARC(System.IntPtr arr, uint len, uint row, uint cul);

                [DllImport("MlLib.dll")]
                public static extern ID nativeMatrixMultiply(ID lId, ID rId);

                [DllImport("MlLib.dll")]
                public static extern ID nativeMatrixAddSC(ID lId, double value);

                [DllImport("MlLib.dll")]
                public static extern bool nativeMatrixPrint(ID id);

                [DllImport("MlLib.dll")]
                public static extern BOOL nativeMatrixEquals(ID lId, ID rId);

            }
        }

        /// <summary>
        ///  MatrixClass
        /// [x1, x2]
        /// </summary>
        public class Matrix1x2 {
            private double[] x1x2 = new double[] {0, 0};

            public Matrix1x2(double[] x1x2) {
                this.x1x2 = x1x2;
            }

            public Matrix1x2(double x1, double x2) : this(new double[] { x1, x2 }) { }

            public double GetX1() {
                return x1x2[0];

            }

            public double DotProduct(Matrix2x1 mat21) {
                return this.GetX1() * mat21.GetX1() + this.GetX2() * mat21.GetY1();
            }

            public static double operator*(Matrix1x2 lhs, Matrix2x1 rhs) {
                return lhs.DotProduct(rhs);
            }

            public Matrix1x2 Multiply(double v) {
                x1x2[0] = GetX1() * v;
                x1x2[1] = GetX2() * v;
                return this;
            }

            public override string ToString() {
                return "{ " + GetX1() + ", " +GetX2() + " }";
            }

            public double GetX2() {
                return x1x2[1];
            }
        }

        /// <summary>
        ///  MatrixClass
        /// [x1]
        /// [y1]
        /// </summary>
        public class Matrix2x1 {
            private double[] x1y1 = new double[] {0, 0};

            public Matrix2x1(double[] x1y1) {
                this.x1y1 = x1y1;
            }

            public Matrix2x1(double x1, double y1) : this(new double[] { x1, y1 }) { }

            public double GetX1() {
                return x1y1[0];
            }

            public double GetY1() {
                return x1y1[1];
            }

            public Matrix2x1 add(double v) {
                return new Matrix2x1(new double[] { GetX1() + v, GetY1() + v });
            }

            public Matrix2x1 add(Matrix2x1 v) {
                return new Matrix2x1(new double[] { GetX1() + v.GetX1(), GetY1() + v.GetY1() });
            }

            public Matrix2x1 Multiply(double v) {
                var x1 = GetX1() * v;
                var y1 = GetY1() * v;
                return new Matrix2x1(new double[] { x1, y1 });
            }
            public override string ToString() {
                return "{ " + GetX1() + ", " +GetY1() + " }";
            }

            public static Matrix2x1 operator+(Matrix2x1 lhs, Matrix2x1 rhs) {
                return lhs.add(rhs);
            }

            public static Matrix2x1 operator+(Matrix2x1 lhs, double rhs) {
                return lhs.add(rhs);
            }

        }
#endregion
    } // Myk.Lib namespace end

    // ノードを表すクラス。h
    class Node {
        private double _output;
        public double output { get { return _output; } }
        public double input1 { set; get; }
        public double input2 { set; get; }
        public double bias { set; get; }
        public double weight1 { set; get; }
        public double weight2 { set; get; }

        private static double Affine(Matrix1x2 x, Matrix2x1 w, double bias) {
            return x * w + bias;
        }

        public void Run() {
            var x = new Matrix1x2(input1, input2);
            var w = new Matrix2x1(weight1, weight2);
            _output = Affine(x, w, bias);
        }
    }
    class Program {
#region data
        const double E = 2.71828182846;
        static readonly double[] 教師データ = { 
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D,
            0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D
    };
#endregion
        // 初期バイアス
        static double bias = 1; 
        // 初期重み
        static Matrix2x1 weightW1W2 = new Matrix2x1(new double[] {1D, 1D}).Multiply(学習率);
        // 学習率
        const double 学習率 = 0.5D;
        // 初期入力(x1, x2)
        static readonly Matrix1x2 paraX1X2 = new Matrix1x2(new double[] { 1D, 1D });


        /// <summary>
        /// 活性化関数（ステップ関数）
        /// </summary>
        /// <param name="x"></param>
        /// <returns>結果</returns>
        public static int StepFunc(double x) {
            /* xを絶対値で割ると1か-1になり+1をすると0か2になる ÷2をすると0か1になり、ステップ関数になる */
            return (int)((x / Math.Abs(x)) + 1) / 2;
        }

        /// <summary>
        /// 活性化関数（シグモイド関数）
        /// </summary>
        /// <param name="x"></param>
        /// <returns></returns>
        public static double Sigmoid(double x) {
            return 1 / (1 + Math.Pow(x, E));
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="w"></param>
        /// <param name="bias"></param>
        /// <returns></returns>
        public static double Affine(Matrix1x2 x, Matrix2x1 w, double bias) {
            return x * w + bias;
        }

        const double d = 1E-5D;
        const double dd = 1E-5D * 2;
        /// <summary>
        /// 数値微分をするメソッド
        /// </summary>
        /// <param name="x">微分する値</param>
        /// <param name="f">対象の式</param>
        /// <returns>傾き</returns>
        public static double Bibun(double x, Func<double, double> f) {
            return (f(x + d) - f(x - d)) / dd;
        }
        /// <summary>
        /// 数値微分をするメソッド
        /// </summary>
        /// <param name="x">微分する値</param>
        /// <param name="f">対象の式</param>
        /// <returns>傾き</returns>
        public static decimal Bibun(decimal x, Func<decimal, decimal> f) {
            var d = 1E-7M;
            return (f(x + d) - f(x - d)) / (2*d);
        }

        /// <summary>
        /// 勾配を計算をします
        /// </summary>
        /// <param name="x1"></param>
        /// <param name="x2"></param>
        /// <param name="f"></param>
        /// <returns>勾配(x2を固定し、x1軸の傾き, x1を固定しx2軸の傾き)</returns>
        public static (double, double) NumericGrad(double x1, double x2,
            Func<double, double, double> f) {
            double gradX1 = (f(x1 + d, x2) - f(x1 - d, x2)) / dd;
            double gradX2 = (f(x1, x2 + d) - f(x1, x2 - d)) / dd;
            return (gradX1, gradX2);
        }

        //public static double GradDiscent(double x1, double x2, Func<double, double, double> f) {
        //    (double, double) dX1dX2 = HenBibun(x1, x2, f);
        //}

        /// <summary>
        /// SoftMax関数
        /// </summary>
        /// <param name="x"></param>
        /// <returns></returns>
        public static double[] SoftMax(double[] x) {
            double[] answer = new double[x.Length];
            double bunbo = 0;
            for (int i = 0; i < x.Length; ++i) {
                bunbo += Math.Pow(E, x[i]);
            }
            for (int i = 0; i < x.Length; ++i) {
                answer[i] = Math.Pow(E, x[i]) / bunbo;
            }
            return answer;
        }


        static void Routine(Matrix2x1 weight, double bias, int count) {
            if (0 >= count) return;
            if (教師データ.Length < count) Console.WriteLine(
                "学習回数が多すぎます。/n学習データは " + 教師データ.Length + " 個なのでそれ以下に設定してください。");
            double  output      = StepFunc(Affine(paraX1X2, weight, bias));
            var     dE          = 教師データ[教師データ.Length - count] - output;
            var     dWeight     = weight.Multiply(dE * 学習率);
            var     dBias       = dE * 学習率 * bias;
            var     newWeight   = dWeight + weight;
            var     newBias     = dBias + bias;
            Console.WriteLine("出力= "          + output);
            Console.WriteLine("dE= "            + dE);
            Console.WriteLine("dWeight= "       + dWeight);
            Console.WriteLine("dBias= "         + dBias);
            Console.WriteLine("newWeight= "     + newWeight);
            Console.WriteLine("newBias= "       + newBias);
            Console.WriteLine("================学習残り " + (count - 1) + " 回===========================");
            Routine(newWeight, newBias, --count);
        }

        [STAThread]
        static void Main() {
            CMatrix cm  = new CMatrix(new double[3, 3] { { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 } });
            CMatrix cm2 = new CMatrix(new double[2, 3] { { 1, 2, 3 }, { 1, 2, 3 } });
            
            Console.WriteLine(cm == cm2);
            #region テストコード
            //Routine(weightW1W2, bias, 教師データ.Length);
            //Routine(weightW1W2, bias, 3);
            //ICollection<int> list = new LinkedList<int>();
            //ICollection<int> list = new List<int>(100000);
            //for (int i = -50000; i < 50000; i++) {
            //    list.Add(i / 20);
            //}

            //Stopwatch sw = new Stopwatch();
            //for (int k = 0; k < 5; k++) {
            //    Func<decimal, decimal> g = (x) => x * x;
            //    sw.Start();
            //    foreach (int i in list) {
            //        decimal result2 = Bibun(i, g);
            //    }
            //    sw.Stop();
            //    var time = sw.ElapsedMilliseconds;
            //    Console.WriteLine(" LinkedList + decimal:" + time + " ms");
            //    sw.Reset();

            //    Func<double, double> f = (x) => x * x;
            //    sw.Start();
            //    foreach (int i in list) {
            //        double result2 = Bibun(i, f);
            //    }
            //    sw.Stop();
            //    time = sw.ElapsedMilliseconds;
            //    Console.WriteLine(" LinkedList + double:" + time + " ms");
            //}

            //Console.WriteLine("===============================================");

            //for (int j = 0; j < 5; j++) {
            //    Func<decimal, decimal> g = (x) => x * x;
            //    sw.Start();
            //    for (int i = -50000; i < 50000; i++) {
            //        decimal result2 = Bibun(i / 20, g);
            //    }
            //    sw.Stop();
            //    var t = sw.ElapsedMilliseconds;
            //    Console.WriteLine("forloop + decimal: " + t + " ms");
            //    sw.Reset();

            //    Func<double, double> f = (x) => x * x;
            //    sw.Start();
            //    for (int i = -50000; i < 50000; i++) {
            //        double result = Bibun(i / 20, f);
            //    }
            //    sw.Stop();
            //    t = sw.ElapsedMilliseconds;
            //    Console.WriteLine("forloop + double: " + t + " ms");
            //}
            #endregion
            //Application.Run(new Form1());

        }

    }

} // Myk namespace end

public static class NativeMethod {
    [DllImport("MlLib.dll")]
    public static extern int fnMlLib();
}
#endif