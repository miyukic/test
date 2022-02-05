using System;
using Myk.Lib;



namespace Myk {
    namespace Lib {

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

            public Matrix1x2 Multiply(double v) {
                x1x2[0] = GetX1() * v;
                x1x2[1] = GetX2() * v;
                return this;
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

            public Matrix2x1 Multiply(double v) {
                x1y1[0] = GetX1() * v;
                x1y1[1] = GetY1() * v;
                return this;
            }

        }
    } // Myk.Lib namespace end

    class Program {
        const double E = 2.71828182846;

        static readonly double[] 教師データ = { 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D, 0D};
        const double b = 1; // バイアス
        const double 学習率 = 0.5D;
        static readonly Matrix2x1 weightW1W2 = new Matrix2x1(new double[] {1D, 1D}).Multiply(学習率);

        static int StepFunc(double x) {
            return (int)(x / Math.Abs(x));
        }

        static void Main() {
            var paraX1X2 = new Matrix1x2(new double[] {1D, 1D});
            double resultY = StepFunc(paraX1X2.DotProduct(weightW1W2) + b);
            Console.WriteLine(resultY);
//            Console.
        }
    }

} // Myk namespace end