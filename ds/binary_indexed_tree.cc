// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp
// https://atcoder.jp/contests/abc221/editorial/2718

#include <iostream>
#include <vector>
using namespace std;

struct binary_indexed_tree {
  int N;
  vector<int> bit;
  binary_indexed_tree(int n) : N(n) {
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

int main() {
  int n, q;
  cin >> n >> q;
  binary_indexed_tree bit(n);
  for (int i = 0; i < q; i++) {
    int com, x, y;
    cin >> com >> x >> y;
    switch (com) {
    case 0: {  // add
      bit.add(x, y);
      break;
    }
    case 1: {  // getSum
      int ans =  bit.sum(y);
      if (x > 1) {
        ans -= bit.sum(x - 1);
      }
      cout << ans << endl;
      break;
    }
    }
  }
  return 0;
}
