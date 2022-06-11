// https://algo-logic.info/binary-indexed-tree/
// Not verified

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template<class T> struct binary_indexed_tree_gcd {
  int N;
  vector<T> bit;  // 1-indexed
  binary_indexed_tree_gcd() {}
  binary_indexed_tree_gcd(int n) : N(n) {
    bit.resize(N + 1, -1);
  }
  void resize(int n) {
    N = n;
    bit.resize(N + 1, -1);
  }
  // Add x to a[k], O(logN)
  // k: 1-indexed
  void add1(int k, T x) {
    for (; k <= N; k += (k & -k)) {
      if (bit[k] < 0) {
        bit[k] = x;
      } else {
        bit[k] = __gcd(bit[k], x);
      }
    }
  }
  // k: 0-indexed
  void add0(int k, T x) {
    add1(k + 1, x);
  }
  // Returns gcd(a[1], a[2], ...,  a[k]), O(logN)
  // k: 1-indexed
  T gcd1(int k) {
    T ret = -1;
    for (; k > 0; k -= (k & -k)) {
      if (ret < 0) {
        ret = bit[k];
      } else {
        ret = __gcd(ret, bit[k]);
      }
    }
    return ret;
  }
  // k: 0-indexed
  T gcd0(int k) {
    return gcd1(k + 1);
  }
};
