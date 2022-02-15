#if NET6_0
#nullable enable

using System;
using System.Collections.Generic;
using System.Diagnostics;
using Myk.Lib;


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
        //(x1, x2)
        public class Matrix1x2 {
            private double[] x1x2 = new double[] {0, 0};

            public Matrix1x2(double[] x1x2) {
                this.x1x2 = x1x2;
            }

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
        // (x1)
        // (y1)
        public class Matrix2x1 {
            private double[] x1y1 = new double[] {0, 0};

            public Matrix2x1(double[] x1y1) {
                this.x1y1 = x1y1;
            }

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

        /// <summary>
        /// 数値微分をするメソッド
        /// </summary>
        /// <param name="x">微分する値</param>
        /// <param name="f">対象の式</param>
        /// <returns>傾き</returns>
        public static double Bibun(double x, Func<double, double> f) {
            var d = 1E-5D;
            return (f(x + d) - f(x - d)) / (2*d);
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
            //Routine(weightW1W2, bias, 教師データ.Length);
            //Routine(weightW1W2, bias, 3);
            //ICollection<int> list = new LinkedList<int>();
            ICollection<int> list = new List<int>(100000);
            for (int i = -50000; i < 50000; i++) {
                list.Add(i / 20);
            }

            Stopwatch sw = new Stopwatch();
            for (int k = 0; k < 5; k++) {
                Func<decimal, decimal> g = (x) => x * x;
                sw.Start();
                foreach (int i in list) {
                    decimal result2 = Bibun(i, g);
                }
                sw.Stop();
                var time = sw.ElapsedMilliseconds;
                Console.WriteLine(" LinkedList + decimal:" + time + " ms");
                sw.Reset();

                Func<double, double> f = (x) => x * x;
                sw.Start();
                foreach (int i in list) {
                    double result2 = Bibun(i, f);
                }
                sw.Stop();
                time = sw.ElapsedMilliseconds;
                Console.WriteLine(" LinkedList + double:" + time + " ms");
            }

            Console.WriteLine("===============================================");

            for (int j = 0; j < 5; j++) {
                Func<decimal, decimal> g = (x) => x * x;
                sw.Start();
                for (int i = -50000; i < 50000; i++) {
                    decimal result2 = Bibun(i / 20, g);
                }
                sw.Stop();
                var t = sw.ElapsedMilliseconds;
                Console.WriteLine("forloop + decimal: " + t + " ms");
                sw.Reset();

                Func<double, double> f = (x) => x * x;
                sw.Start();
                for (int i = -50000; i < 50000; i++) {
                    double result = Bibun(i / 20, f);
                }
                sw.Stop();
                t = sw.ElapsedMilliseconds;
                Console.WriteLine("forloop + double: " + t + " ms");
            }

            //Application.Run(new Form1());
        }

    }

} // Myk namespace end
#endif