// https://atcoder.jp/contests/abc269/tasks/abc269_g

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

/**
 * スライド最小値
 * 計算量
 *   push: すべての配列要素に対してpushを計算する時、ならしO(1)
 *   get: すべての配列要素に対してgetを計算する時、ならしO(1)
 */
template<class T> struct SlideMin {
  SlideMin() {}
  deque<pair<int, T> > q;
  void push(int i, T x) {
    while (!q.empty() && q.back().second >= x) {
      q.pop_back();
    }
    q.push_back(make_pair(i, x));
  }
  T get(int l) {  // l以上の中での最小値を返す
    while (!q.empty() && q.front().first < l) {
      q.pop_front();
    }
    assert(!q.empty());
    return q.front().second;
  }
};

int main() {
  int N, M;
  cin >> N >> M;
  int suma = 0;
  vector<int> D(N);
  int sl = 0;
  int sr = 0;
  map<int, int> mp;
  for (int n = 0; n < N; n++) {
    int a, b;
    cin >> a >> b;
    int d = b - a;
    suma += a;
    D.at(n) = d;
    if (d > 0) {
      sr += d;
    } else {
      sl += -d;
    }
    mp[d]++;
  }
  int w = sl + sr;
  const int INF = 1e9;
  vector<int> dp(w + 1, INF);
  dp[sl] = 0;
  for (auto [_d, c] : mp) {
    if (_d == 0) {
      continue;
    }
    bool neg = false;
    if (_d < 0) {
      neg = true;
      reverse(dp.begin(), dp.end());
    }
    vector<int> p(w + 1, INF);
    swap(dp, p);
    int d = abs(_d);
    // 過去c個のスライド最小値
    for (int si = 0; si < d; si++) {  // si: dで割った時の余り
      SlideMin<int> sm;
      for (int i = si; i <= w; i += d) {
        sm.push(i, p[i] - i / d);
        dp[i] = sm.get(i - d * c) + i / d;
      }
    }
    if (neg) {
      reverse(dp.begin(), dp.end());
    }
  }
  vector<int> ans(M + 1, -1);
  for (int i = 0; i <= w; i++) {
    if (dp[i] == INF) {
      continue;
    }
    int j = suma + i - sl;
    assert(0 <= j && j <= M);
    ans[suma + i - sl] = dp[i];
  }
  for (int m = 0; m <= M; m++) {
    cout << ans.at(m) << '\n';
  }
  return 0;
}
