﻿#if NET6_0
#nullable enable

using System;
using System.Collections.Generic;
using System.Diagnostics;
using Myk.Lib;
using System.Runtime.InteropServices;


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
    }　// Myk.Util namespace end
    namespace Lib {

#region Matrix

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

        public void run() {
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
            int ret = NativeMethod.fnMlLib();
            Console.WriteLine("NativeMethod#fnMlib = " + ret);
            if (IntPtr.Size == 8) {
                Console.WriteLine();
            } else if (IntPtr.Size == 4) {
                Console.WriteLine();
            }
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

            //Application.Run(new Form1());
        }

    }

} // Myk namespace end

public static class NativeMethod {
    [DllImport("MlLib.dll")]
    public static extern int fnMlLib();
}
#endif