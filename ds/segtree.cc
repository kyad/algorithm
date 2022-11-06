// https://atcoder.jp/contests/abc276/tasks/abc276_f
// https://algo-logic.info/segment-tree/
// https://qiita.com/drken/items/68b8503ad4ffb469624c

#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;

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

  // 初期化 O(N)
  void set0(int i, X x) { dat[i + n - 1] = x; }  //  i: 0-indexed. dat[n-1]~dat[2n-2]に値が入る
  void set1(int i, X x) { set0(i - 1, x); }  // i: 1-indexed
  void build() {
    for (int k = n - 2; k >= 0; k--) {
      dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
    }
  }

  // データ取得 O(1)
  X get0(int i) { return dat[i + n - 1]; }  // i: 0-indexed
  X get1(int i) { return get0(i - 1); }  // i: 1-indexed

  // 1点更新クエリ O(logN)
  void update0(int i, X x) {  // i: 0-indexed
    i += (n - 1);
    dat[i] = x;
    while (i > 0) {  // 最下段から上がる
      i = (i - 1) / 2;  // parent
      dat[i] = fx(dat[i * 2 + 1], dat[i * 2 + 2]);
    }
  }
  void update1(int i, X x) { update0(i - 1, x); }  // i: 1-indexed

  // 1点加算クエリ O(logN)
  void add0(int i, X x) { update0(i, get0(i) + x); }  // i: 0-indexed
  void add1(int i, X x) { add0(i - 1, x); }  // 1-indexed

  // 範囲取得クエリ O(logN) [a, b)
  X query0(int a, int b) { return query_sub(a, b, 0, 0, n); }  // a, b: 0-indexed
  X query1(int a, int b) { return query0(a - 1, b - 1); }  // a, b: 1-indexed
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

// 1点更新、区間最小値取得 (RMQ, Range Minimum Query)
// auto fx = [](int x1, int x2) -> int { return min(x1, x2); };
// SegTree<int> rmq(n, fx, INF);

// 1点更新、区間最大値取得 (Range Maximum Query)
// auto fx = [](int x1, int x2) -> int { return max(x1, x2); };
// SegTree<int> rmq(n, fx, -INF);

// 1点更新、区間和
// auto fx = [](long long x1, long long x2) -> long long { return x1 + x2; };
// SegTree<long long> seg(M, fx, 0);

// 1点更新、区間のGCD取得
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
  int N;
  cin >> N;
  vector<int> A(N);
  const int M = 200000;
  for (int n = 0; n < N; n++) {
    cin >> A.at(n);
  }
#if 1
  auto fx = [](long long x1, long long x2) -> long long { return x1 + x2; };
  SegTree<long long> seg(M, fx, 0);
  SegTree<long long> count(M, fx, 0);
#else
  binary_indexed_tree<long long> seg(M);
  binary_indexed_tree<long long> count(M);
#endif
  // dp
  vector<mint> dp(N, 0);
  dp[0] = A[0];
  {
    int x = A[0];
    seg.add1(x, x);
    count.add1(x, 1);
  }
  for (int i = 1; i < N; i++) {
    mint iinv = mint(1) / mint(i + 1);
    mint ex1 = (mint(i) * iinv) * (mint(i) * iinv) * dp[i - 1];
    dp[i] += ex1;
    mint ex2 = iinv * iinv * A[i];
    dp[i] += ex2;
    // etc
    int x = A[i];
#if 1
    long long sum = seg.query1(x, M + 1);
#else
    long long sum = seg.sum1(M) - seg.sum1(x);
#endif
    mint ex3 = iinv * iinv * 2 * mint(sum);
    dp[i] += ex3;
    
#if 1
    long long num = count.query1(1, x);
#else
    long long num = count.sum1(x);
#endif
    mint ex4 = iinv * iinv * 2 * x * mint(num);
    dp[i] += ex4;
    // Update
    seg.add1(x, x);
    count.add1(x, 1);
  }
  for (int n = 0; n < N; n++) {
    cout << dp[n].val() << '\n';
  }
  return 0;
}
