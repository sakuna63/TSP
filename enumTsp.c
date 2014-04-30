/// ### 
/// int tspSolver(void) を宣言して，その中に自分のアルゴリズムを書いてください．
/// 入出力データはグローバル変数でやりとりします．
/// 入力データは 都市数 n，都市座標の二次元配列 city[n][2] として入力されます．
/// 出力データは 順回路 tour[n], 順回路長 length で出力しますが，
/// length は最後に計算し直されるので，あまり出力する意味はありません．

/// 使用するグローバル変数等．必須項目
#define MAX 20000

#include<math.h>
#include<limits.h>
#include<stdlib.h>
#include<stdio.h>

extern int n, length, tour[MAX];
extern float city[MAX][2];

/// 順回路表示のための関数
/// tou[] に順回路の配列を，wai にウェイト時間(ミリ秒)，colorに色 0~3を指定．
extern void showTour(int *tou, int wai, int color);
/// color[] に配列を指定して，枝ごとに色を変えられる順回路表示．
extern void showCTour(int *tou, int wai, int *color);
/// 文字列を表示ウィンドウの上部バーに表示．数字等が表示したい場合 sprintf 等と組み合わせる．
extern void showString(char *str);
/// leng を暫定解として表示(標準エラー出力)
extern void showLength(int leng);
/// ###

int tr[MAX];

/// 距離の計算はこの関数と同等の方法で行う．
/// 必ずしもこの関数を残しておく必要は無い．
int Dis(int i, int j)
{
  float xd, yd;

  xd = city[i][0] - city[j][0];
  yd = city[i][1] - city[j][1];
  return (int)(sqrt(xd * xd + yd * yd) + .5);
}

// 動的計画法によって最適解を求める関数
int dynamic() {
  int i, j ,S, tmp, SMAX, *f[n];

  // 各点の経由状態をビットフラグで表現した場合の最大値(2^n - 1)を計算する
  SMAX = 1 << n;

  // メモリ確保
  for ( i = 0; i < n; i++)
    f[i] = (int *)malloc(sizeof(int) * SMAX);

  // 配列をすべて初期化しておく
  for (S = 1; S < SMAX; S++)
    for (i = 0; i < n; i++)
      f[i][S] = 1000000;

  // 始点をn-1として、始点-点i間の距離を計算しておく
  for ( i = 0; i < n-1; i++)
    f[i][1<<i] = Dis(n-1, i);

  for (S = 1; S < SMAX; S++) {
    // iを含む部分集合Sを経て点iに至った場合について距離を計算する
    for ( i = 0; i < n; i++) {

      // 部分集合にiが含まれていなかった場合は計算しない
      if(!((1<<i) & S)) continue;

      // 点iからjまでの距離を加算する
      for ( j = 0; j < n; j++) {

        // jが部分集合に含まれていた場合は計算しない
        if ((1<<j) & S) continue;

        // f[i][S]:iを含む部分集合Sを得てiに至った場合の最短距離
        tmp = f[i][S] + Dis(i,j);
        printf("i:%d,j:%d,S:%d,tmp:%d\n", i, j, S, tmp);
        if (tmp < f[j][(S | (1<<j))])
          f[j][(S | (1<<j))] = tmp;
      }
    }
  }
  return f[n-1][SMAX-1];
}

int tspSolver(void)
{
  length = dynamic();
  return 1;
}
