// https://atcoder.jp/contests/abc253/tasks/abc253_f
// https://algo-logic.info/binary-indexed-tree/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template<class T> struct binary_indexed_tree {
  int N;
  vector<T> bit;  // 1-indexed
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
  void add1(int k, T x) {
    for (; k <= N; k += (k & -k)) {
      bit[k] += x;
    }
  }
  // k: 0-indexed
  void add0(int k, T x) {
    add1(k + 1, x);
  }
  // Returns a[1] + a[2] + ... + a[k], O(logN)
  // k: 1-indexed
  T sum1(int k) {
    T ret = 0;
    for (; k > 0; k -= (k & -k)) {
      ret += bit[k];
    }
    return ret;
  }
  // k: 0-indexed
  T sum0(int k) {
    return sum1(k + 1);
  }
  // Returns minimum x such that a[1] + a[2] + ... + a[x] >= w, O(logN)
  // return: 1-indexed (0: not found)
  T lower_bound1(T w) {
    if (w <= 0) {
      return 0;
    } else {
      T x = 0;
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
  T lower_bound0(T w) {
    return lower_bound1(w) - 1;
  }
};

// BITの区間加算・1点取得はimos法の値をbitで管理する。
// binary_indexed_tree<long long> bit(N + 1);
// [l, r]にxを加算：add(l, x), add(r + 1, x)
// 1点iの取得：sum(0, i)

int main() {
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<vector<int> > query(Q, vector<int>(4));
  vector<pair<int, int> > adds;  // 加算クエリ
  vector<vector<pair<int, int> > > sums(1);  // 答えを計算するためのクエリ。1は下駄
  vector<int> last(N), val(N, 0);  // 行iに最後にセットされた時刻、その時のx
  vector<long long> ans;  // ai番目の答え
  vector<int> js;  // ai番目のj
  for (int q = 0; q < Q; q++) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      l--;
      adds.push_back(make_pair(l, x));
      adds.push_back(make_pair(r, -x));
      sums.push_back(vector<pair<int, int> >());
      sums.push_back(vector<pair<int, int> >());
    } else if (type == 2) {
      int i, x;
      cin >> i >> x;
      i--;
      last[i] = adds.size();  // addsのサイズを時刻にする。下駄が必要
      val[i] = x;
    } else {
      int i, j;
      cin >> i >> j;
      i--;
      j--;
      int ai = ans.size();  // 出力クエリのindex
      ans.push_back(val[i]);  // ans[ai]
      js.push_back(j);  // js[ai]
      sums[last[i]].push_back(make_pair(ai, -1));  // 2回目のループで、ans[ai]にbitの和の不要部分を引いてもらう
      sums[adds.size()].push_back(make_pair(ai, 1));  // 2回目のループで、ans[ai]にbitの和を足してもらう。下駄が必要
    }
  }
  binary_indexed_tree<long long> bit(M + 2);
  for (int t = 0; t < (int)adds.size() + 1; t++) {  // +1は下駄分
    for (size_t i = 0; i < sums[t].size(); i++) {
      int ai = sums[t][i].first;
      int c = sums[t][i].second;
      ans[ai] += bit.sum0(js[ai]) * c;
    }
    if (t == adds.size()) {
      break;  // addsには下駄を履かせていないため
    }
    bit.add0(adds[t].first, adds[t].second);
  }
  for (int ai = 0; ai < (int)ans.size(); ai++) {
    cout << ans[ai] << endl;
  }
  return 0;
}
