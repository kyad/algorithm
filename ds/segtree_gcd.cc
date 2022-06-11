// https://atcoder.jp/contests/abc254/tasks/abc254_f
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

// GCD
// const int ex = -1;  // 約数に全ての数を持つ数とする
// auto fx = [&ex](int x1, int x2) -> int {
//   if (x1 == ex) {
//     return x2;
//   } else if (x2 == ex) {
//     return x1;
//   } else {
//     return __gcd(x1, x2);
//   }
// };
// SegTree<int> gcd(n, fx, ex);

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> A.at(i);
  }
  for (int i = 0; i < N; i++) {
    cin >> B.at(i);
  }
  const int ex = -1;
  auto fx = [&ex](int x1, int x2) -> int {
    if (x1 == ex) {
      return x2;
    } else if (x2 == ex) {
      return x1;
    } else {
      return __gcd(x1, x2);
    }
  };
  SegTree<int> da(N - 1, fx, ex);
  SegTree<int> db(N - 1, fx, ex);
  for (int i = 0; i < N - 1; i++) {
    da.set(i, abs(A.at(i + 1) - A.at(i)));
    db.set(i, abs(B.at(i + 1) - B.at(i)));
  }
  da.build();
  db.build();
  for (int q = 0; q < Q; q++) {
    int H1, H2, W1, W2;
    cin >> H1 >> H2 >> W1 >> W2;
    H1--; H2--; W1--; W2--;
    int ans = A.at(H1) + B.at(W1);
    if (H2 > H1) {
      int now = da.query(H1, H2);
      ans = __gcd(ans, now);
    }
    if (W2 > W1) {
      int now = db.query(W1, W2);
      ans = __gcd(ans, now);
    }
    cout << ans << endl;
  }
  return 0;
}
