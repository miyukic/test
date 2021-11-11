#include <stdio.h> // 駒の文字(先手:X 後手:O)
char koma[2] = {'X', 'O'};

// 盤表示関数
void print_board(char board[])
{
  printf("%c|%c|%c\n", board[0], board[1], board[2]);
  printf("%c|%c|%c\n", board[3], board[4], board[5]);
  printf("%c|%c|%c\n", board[6], board[7], board[8]);
}
    // 置けるかチェック関数
int check(char board[], char x)
{
  int i;
  // 入力した文字の範囲判定
  if (x < 'a' || 'i' < x)
  {
    return 0;
  }
  i = x - 'a'; // 'a'～'z'→0～8に変換
  // すでに置かれているか判定
  if (board[i] != x)
  {
    return 0;
  }
  return 1;
}

// メイン関数
int main(void)
{
  char board[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  char x = 'a';
  int turn;
  int teban;
  int ok;

  printf("三目並べを始めます。\n");
  // 9回繰り返し
  for (turn = 0; turn < 9; turn++)
  {
    teban = turn % 2;
    // 置けるマスを入力するまで繰り返し
    ok = 0;
    while (ok == 0)
    {
      print_board(board); // 盤表示
      // 置く場所入力
      printf("どこに%cをいれますか?\n", koma[teban]);
      printf("a～iで指定してください。\n");
      rewind(stdin); // 入力データをクリア(scanfで[Enter]を読んでしまう問題を回避)
      scanf("%c", &x);
      // 置く判定
      if (check(board, x))
      {
        ok = 1;
      }
    }
    // 置く処理
    board[x - 'a'] = koma[teban];
  }
  return 0;
}
