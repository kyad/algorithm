// https://atcoder.jp/contests/arc033/tasks/arc033_3
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
  // Returns minimum x such that a[1] + a[2] + ... + a[x] >= w, O(logN)
  int lower_bound(int w) {
    if (w <= 0) {
      return 0;
    } else {
      int x = 0;
      int r = 1;
      while (r < N) {
        r = r << 1;
      }
      for (int len = r; len > 0; len = len >> 1) {
        if (x + len < N && bit[x + len] < w) {
          w -= bit[x + len];
          x += len;
        }
      }
      return x + 1;
    }
  }
};

int main() {
  int Q;
  cin >> Q;
  binary_indexed_tree bit(200000);
  for (int q = 0; q < Q; q++) {
    int T, X;
    cin >> T >> X;
    switch (T) {
    case 1: {
      bit.add(X, 1);
      break;
    }
    case 2: {
      int value = bit.lower_bound(X);
      cout << value << endl;
      bit.add(value, -1);
      break;
    }
    }
  }
  return 0;
}
