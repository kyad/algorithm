// https://atcoder.jp/contests/typical90/tasks/typical90_be

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
// modint
#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;
ostream& operator<<(ostream& os, const mint &v) {
  os << v.val();
  return os;
}

/**
 * (int, xor)上の掃き出し法
 * 掃き出し法で、行を1次独立にする
 * Aは破壊されて、結果の上三角行列を上書きする。
 * ただし、フルランクでない場合は列の交換は行わず行の交換のみ行い、要素を上に詰める。
 * 返り値：rank
 * 
 * [[1, 1, 1],
 *  [0, 0, 1],
 *  [0, 0, 1],
 *  [0, 0, 0]]
 * ->
 * [[1, 1, 0],
 *  [0, 0, 1],
 *  [0, 0, 0],
 *  [0, 0, 0]]
 */
int sweep_xor(vector<vector<int> >& A) {
  int N = A.size();
  assert(N >= 1);
  int M = A[0].size();
  int i = 0;  // 次に確定させたい行
  for (int j = 0; j < M; j++) {
    // 左からj個目の値が0にならない最初の行kをi行以降で見つける
    int k;
    for (k = i; k < N; k++) {
      if (A[k][j] != 0) {
        break;
      }
    }
    if (k == N) {
      // 左からj個目の値はすべて0になっている。この場合は掃き出し法しなくて良い
      continue;
    }
    // A[i][j]==1になるように、i行目とk行目を入れかえる
    swap(A[i], A[k]);
    // 掃き出し法
    for (int k = 0; k < N; k++) {
      if (k == i) {
        continue;
      }
      if (A[k][j] != 0) {
        for (int l = j; l < M; l++) {
          A[k][l] ^= A[i][l];
        }
      }
    }
    i++;
  }
  for (int ii = i; ii < N; ii++) {
    for (int jj = 0; jj < M; jj++) {
      assert(A[ii][jj] == 0);
    }
  }
  // rank計算
  int rank;
  for (rank = 0; rank < N; rank++) {
    bool all_zero = true;
    for (int j = 0; j < M; j++) {
      if (A[rank][j] == 1) {
        all_zero = false;
        break;
      }
    }
    if (all_zero) {
      break;
    }
  }
  return rank;
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int> > B(N, vector<int>(M, 0));
  for (int n = 0; n < N; n++) {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
      int A;
      cin >> A;
      A--;
      B[n][A] = 1;
    }
  }
  vector<int> S(M);
  for (int m = 0; m < M; m++) {
    cin >> S.at(m);
  }
  int rank = sweep_xor(B);
  // Bで貪欲にSと一致させる
  int i = 0;  // どのスイッチを見ているか
  for (int j = 0; j < M; j++) {
    if (S[j] == 0) {
      // B=[[1 0 0 0 0 0 1] [0 1 0 0 0 0 1] [0 0 1 0 0 0 1] [0 0 0 1 0 0 1]], S=[1 1 1 0 0 0 0]の時、
      // 最初の3個だけ採用したいのに、4個目が採用されるのを防ぐ
      while (i < N && B[i][j] == 1) {
        i++;
      }
      continue;
    }
    assert(S[j] == 1);
    while (i < N && B[i][j] == 0) {
      i++;
    }
    if (i >= N) {  // S[j] == 1なるjが残ったままスイッチが無くなったのでNG
      cout << 0 << endl;
      return 0;
    }
    assert(B[i][j] == 1);
    // B[i]を採用する
    for (int l = j; l < M; l++) {
      S[l] ^= B[i][l];
    }
    i++;
  }
  // Sに完全一致できた
  mint ans(2);
  ans = ans.pow(N - rank);
  cout << ans.val() << endl;
  return 0;
}
