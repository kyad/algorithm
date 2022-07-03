// https://atcoder.jp/contests/abc258/tasks/abc258_e

#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N, Q;
  long long X;
  cin >> N >> Q >> X;
  vector<long long> W(N);
  long long W_sum = 0;
  for (int n = 0; n < N; n++) {
    cin >> W.at(n);
    W_sum += W.at(n);
  }
  long long base = X / W_sum;
  // a[p]: じゃがいもpから始めた時に何個入れられるか
  vector<long long> a(N);
  long long na = base * N;
  long long rem = X % W_sum;
  for (int p = 0; p < N; p++) {
    while (rem > 0) {
      rem -= W[(p + na) % N];
      na++;
    }
    a[p] = na;
    rem += W[p];
    na--;
  }
  // ダブリングテーブル d[m][p]: グラフで考えた時、ノードpから2^m回移動した先のノード番号
  const int D = 41;
  vector<vector<long long> > d(D, vector<long long>(N));
  for (int p = 0; p < N; p++) {
    d[0][p] = (p + a[p]) % N;
  }
  for (int m = 0; m < D - 1; m++) {
    for (int p = 0; p < N; p++) {
      d[m + 1][p] = d[m][d[m][p]];
    }
  }
  for (int q = 0; q < Q; q++) {
    long long K;
    cin >> K;
    K--;
    // ダブリングテーブルを使う
    int p = 0;
    for (int m = D - 1; m >= 0; m--) {
      if ((K >> m) & 1) {
        p = d[m][p];
      }
    }
    cout << a[p] << endl;
  }
  return 0;
}
