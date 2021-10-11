// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja
// https://atcoder.jp/contests/abc221/editorial/2718
// https://algo-logic.info/binary-indexed-tree/

#include <iostream>
#include <vector>
using namespace std;

struct binary_indexed_tree {
  int N;
  vector<int> bit;
  binary_indexed_tree() {}
  binary_indexed_tree(int n) : N(n) {
    bit.resize(N + 1, 0);
  }
  void resize(int n) {
    N = n;
    bit.resize(N + 1, 0);
  }
  // Add x to a[k], O(logN)
  // k: 1-indexed
  void add(int k, int x) {
    for (; k <= N; k += (k & -k)) {
      bit[k] += x;
    }
  }
  // Returns a[1] + a[2] + ... + a[k], O(logN)
  // k: 1-indexed
  int sum(int k) {
    int ret = 0;
    for (; k > 0; k -= (k & -k)) {
      ret += bit[k];
    }
    return ret;
  }
};

struct binary_indexed_tree_raq {
  binary_indexed_tree bit0, bit1;
  binary_indexed_tree_raq(int n) {
    bit0.resize(n);
    bit1.resize(n);
  }
  // Add x to a[l], ... ,a[r], O(logN)
  // l, r: 1-indexed
  void add(int l, int r, int x) {
    bit0.add(l, -x * (l - 1));
    bit1.add(l, x);
    bit0.add(r + 1, x * r);
    bit1.add(r + 1, -x);
  }
  // Returns v[1] + v[2] + ... + v[k], O(logN)
  // k: 1-indexed
  int sum(int k) {
    return bit0.sum(k) + bit1.sum(k) * k;
  }
};
 

int main() {
  int n, q;
  cin >> n >> q;
  binary_indexed_tree_raq bit(n);
  for (int i = 0; i < q; i++) {
    int com;
    cin >> com;
    switch (com) {
    case 0: {  // add
      int s, t, x;
      cin >> s >> t >> x;
      bit.add(s, t, x);
      break;
    }
    case 1: {  // get
      int i;
      cin >> i;
      int ans =  bit.sum(i);
      if (i > 1) {
        ans -= bit.sum(i - 1);
      }
      cout << ans << endl;
      break;
    }
    }
  }
  return 0;
}
