// See https://aka.ms/new-console-template for more information
using System;
using System.Collections.Generic;

namespace Miyuki.Test {
class Program {
    public static List<List<byte>> board = new List<List<byte>>{
        new List<byte>{0,0,0},
        new List<byte>{0,0,0},
        new List<byte>{0,0,0}
    };

    public static void Main(string[] args) {
        
        DrawBoard();

        //Console.WriteLine(" @======@ ");
        //Console.WriteLine("||・・・||");
        //Console.WriteLine("||・・・||");
        //Console.WriteLine("||・・・||");
        //Console.WriteLine(" @======@ ");
    }
    public static void PlacePeaceYX(int x, int y, int type) {
        if (type == 0) {
            board[x][y] = 0;
        } else if (type > 0) {
            board[x][y] = 1;
        } else if (type < 0) {
            board[x][y] = -1;
        }
    }

    public static void DrawBoard() {
        Console.WriteLine(" @===@ ");
        foreach (var list in Program.board) {
            Console.Write("||");
            foreach (var v in list) {
                if (v == 0) {
                    Console.Write("▪");
                } else if (v > 0) {
                    Console.Write("○");
                } else if (v < 0) {
                    Console.Write("●");
                }
            }
            Console.WriteLine("||");
        }
        Console.WriteLine(" @===@ ");
    }
}
}
