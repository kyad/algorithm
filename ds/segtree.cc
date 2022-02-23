// https://atcoder.jp/contests/abc228/tasks/abc228_f
// https://algo-logic.info/segment-tree/
// https://qiita.com/drken/items/68b8503ad4ffb469624c

#include <functional>
#include <iostream>
#include <vector>
using namespace std;

// 抽象化したセグメント木
template<class X> struct SegTree {
  using FX = function<X(X, X)>;
  int n;  // n_以上の最小の2べき
  FX fx;  // 二項演算 X x X -> X
  const X ex;  // 単位元
  vector<X> dat;  // dat[0]~dat[2*n-2]に値が入る

  SegTree(int n_, FX fx_, X ex_): n(), fx(fx_), ex(ex_) {
    int x = 1;
    while (n_ > x) {
      x *= 2;
    }
    n = x;
    dat.resize(2 * n - 1, ex_);
  }

  // 初期化 O(N) i: 0-indexed
  void set(int i, X x) { dat[i + n - 1] = x; }  // dat[n-1]~dat[2n-2]に値が入る
  void set1(int i, X x) { set(i - 1, x); }  // 1-indexed
  void build() {
    for (int k = n - 2; k >= 0; k--) {
      dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
    }
  }

  // 更新クエリ O(logN) i: 0-indexed
  void update(int i, X x) {
    i += (n - 1);
    dat[i] = x;
    while (i > 0) {  // 最下段から上がる
      i = (i - 1) / 2;  // parent
      dat[i] = fx(dat[i * 2 + 1], dat[i * 2 + 2]);
    }
  }
  void update1(int i, X x) { update(i - 1, x); }  // 1-indexed

  // 取得クエリ O(logN) [a, b), a, b: 0-indexed
  X query(int a, int b) { return query_sub(a, b, 0, 0, n); }
  X query1(int a, int b) { return query(a - 1, b - 1); }  // 1-indexed
  X query_sub(int a, int b, int k, int l, int r) {
    // k: 現在見ているノードの位置 [l, r): dat[k]が表している区間
    if (r <= a || b <= l) {  // 範囲外
      return ex;
    } else if (a <= l && r <= b) {  // 範囲内
      return dat[k];
    } else {  // 一部区間が被る時
      X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
      X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
      return fx(vl, vr);
    }
  }
};

template<class X> ostream& operator<<(ostream& os, const SegTree<X> &segtree) {
  int depth = 0;
  int temp = segtree.n;
  while (temp > 0) {
    temp /= 2;
    depth++;
  }
  for (int d = 0; d < depth; d++) {
    int left = (1<<d) - 1;
    int right = (1<<(d+1)) - 1;
    for (int i = left; i < right; i++) {
      os << segtree.dat[i];
      os << (i == right - 1 ? '\n' : ' ');
    }
  }
  return os;
}

// RMQ (Range Minimum Query)
// auto fx = [](int x1, int x2) -> int { return min(x1, x2); };
// SegTree<int> rmq(n, fx, INF);

// Range Maximum Query
// auto fx = [](int x1, int x2) -> int { return max(x1, x2); };
// SegTree<int> rmq(n, fx, -INF);

int main() {
  auto fx = [](long long x1, long long x2) -> long long { return max(x1, x2); };
  int H, W, h1, w1, h2, w2;
  cin >> H >> W >> h1 >> w1 >> h2 >> w2;
  h2 = min(h2, h1);
  w2 = min(w2, w1);
  vector<vector<long long> > A(H + 1, vector<long long>(W + 1, 0));  // 1-indexed
  for (int y = 1; y <= H; y++) {
    for (int x = 1; x <= W; x++) {
      cin >> A.at(y).at(x);
    }
  }
  for (int y = 1; y <= H; y++) {
    for (int x = 1; x <= W; x++) {
      A[y][x] += A[y][x - 1];
    }
  }
  for (int x = 1; x <= W; x++) {
    for (int y = 1; y <= H; y++) {
      A[y][x] += A[y - 1][x];
    }
  }
  // Taka[y][x]: (x, y)から(x+w1, y+h1)までの和 (1-indexed)
  vector<vector<long long> > Taka(H - h1 + 1 + 1, vector<long long>(W - w1 + 1 + 1, 0));
  for (int y = 1; y <= H - h1 + 1; y++) {
    for (int x = 1; x <= W - w1 + 1; x++) {
      Taka[y][x] = A[y + h1 - 1][x + w1 - 1] - A[y + h1 - 1][x - 1] - A[y - 1][x + w1 - 1] + A[y - 1][x - 1];
    }
  }
  // Aoki[y][x]: (x, y)から(x+w2, y+h2)までの和 (1-indexed)
  vector<vector<long long> > Aoki(H - h2 + 1 + 1, vector<long long>(W - w2 + 1 + 1, 0));
  for (int y = 1; y <= H - h2 + 1; y++) {
    for (int x = 1; x <= W - w2 + 1; x++) {
      Aoki[y][x] = A[y + h2 - 1][x + w2 - 1] - A[y + h2 - 1][x - 1] - A[y - 1][x + w2 - 1] + A[y - 1][x - 1];
    }
  }
  // P: Aoki[y][x]のx方向の幅w1-w2+1のスライド最小値
  vector<vector<long long> > P(H - h2 + 1 + 1, vector<long long>(W - w1 + 1 + 1, 0));
  for (int y = 1; y <= H - h2 + 1; y++) {
    SegTree<long long> rmq(W - w2 + 1, fx, 0);  // Range Maximum Query
    for (int x = 1; x <= W - w2 + 1; x++) {
      rmq.set1(x, Aoki[y][x]);
    }
    rmq.build();
    for (int x = 1; x <= W - w1 + 1; x++) {
      P[y][x] = rmq.query1(x, x + w1 - w2 + 1);
    }
  }
  // Q: Aoki[y][x]のx方向の幅w1-w2+1、y方向の幅h1-h2+1のスライド最小値
  vector<vector<long long> > Q(H - h1 + 1 + 1, vector<long long>(W - w1 + 1 + 1, 0));
  for (int x = 1; x <= W - w1 + 1; x++) {
    SegTree<long long> rmq(H - h2 + 1, fx, 0);  // Range Maximum Query
    for (int y = 1; y <= H - h2 + 1; y++) {
      rmq.set1(y, P[y][x]);
    }
    rmq.build();
    for (int y = 1; y <= H - h1 + 1; y++) {
      Q[y][x] = rmq.query1(y, y + h1 - h2 + 1);
    }
  }
  long long ans = 0;
  for (int y = 1; y <= H - h1 + 1; y++) {
    for (int x = 1; x <= W - w1 + 1; x++) {
      ans = max(ans, Taka[y][x] - Q[y][x]);
    }
  }
  cout << ans << endl;
  return 0;
}
