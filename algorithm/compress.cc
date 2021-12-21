// https://atcoder.jp/contests/abc231/tasks/abc231_f
// https://atcoder.jp/contests/abc221/editorial/2718
// https://algo-logic.info/binary-indexed-tree/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct binary_indexed_tree {
  int N;
  vector<int> bit;  // 1-indexed
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
  void add1(int k, int x) {
    for (; k <= N; k += (k & -k)) {
      bit[k] += x;
    }
  }
  // k: 0-indexed
  void add0(int k, int x) {
    add1(k + 1, x);
  }
  // Returns a[1] + a[2] + ... + a[k], O(logN)
  // k: 1-indexed
  int sum1(int k) {
    int ret = 0;
    for (; k > 0; k -= (k & -k)) {
      ret += bit[k];
    }
    return ret;
  }
  // k: 0-indexed
  int sum0(int k) {
    return sum1(k + 1);
  }
  // Returns minimum x such that a[1] + a[2] + ... + a[x] >= w, O(logN)
  // return: 1-indexed (0: not found)
  int lower_bound1(int w) {
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
  // return: 0-indexed (-1: not found)
  int lower_bound0(int w) {
    return lower_bound1(w) - 1;
  }
};

#include <map>
void compress(vector<int>& A) {
  map<int, int> mp;
  for (size_t i = 0; i < A.size(); i++) {
    mp[A[i]]++;
  }
  int count = 0;
  for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
    it->second = count++;
  }
  for (size_t i = 0; i < A.size(); i++) {
    A[i] = mp[A[i]];
  }
}

int main() {
  int N;
  cin >> N;
  vector<int> A(N), B(N);  // 0-indexed
  for (int n = 0; n < N; n++) {
    cin >> A.at(n);
  }
  for (int n = 0; n < N; n++) {
    cin >> B.at(n);
  }
  // Ai <= Aj かつ Bi >= Bj を満たす(i, j)の個数 (転倒数で等号がついた場合)
  compress(A);
  compress(B);
  vector<pair<int, int> > AB(N);  // 0-indexed
  for (int n = 0; n < N; n++) {
    AB.at(n) = make_pair(A.at(n), B.at(n));
  }
  sort(AB.begin(), AB.end());
  map<int, vector<int> > C;
  for (int n = 0; n < N; n++) {
    C[AB[n].first].push_back(AB[n].second);
  }
  long long ans = 0;
  binary_indexed_tree bit(N);
  int count = 0;
  for (map<int, vector<int> >::iterator it = C.begin(); it != C.end(); it++) {
    vector<int> &B = it->second;
    for (size_t i = 0 ; i < B.size(); i++) {
      count++;
      bit.add0(B[i], 1); // 0-indexed
    }
    for (size_t i = 0 ; i < B.size(); i++) {
      ans += count;
      if (B[i] > 0) {
        ans -= bit.sum0(B[i] - 1); // 0-indexed
      }
    }
  }
  cout << ans << endl;
  return 0;
}
