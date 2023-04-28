// https://atcoder.jp/contests/typical90/tasks/typical90_bh

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

/**
 * 最長増加部分列 (Longest Increasing Subsequence, LIS)
 * 計算量 O(NlogN)
 */
template<class T> pair<vector<int>, vector<T> > lis(const vector<T>& X) {
  const int INF = 1e9+1;
  int N = X.size();
  // dp[i]: 長さiの単調増加列の末尾の数字の最小値 (0<=i<=N)
  vector<T> dp(N + 1, INF);
  dp[0] = -INF;
  // len[i]: iまで見た時の最大の単調増加列の長さ (0<=i<N)
  vector<int> len(N, 0);
  // value[i]: iまで見た時の最大の単調増加列の末尾の数字の最小値 (0<=i<N)
  vector<T> value(N, 0);
  for (int i = 0; i < N; i++) {
    vector<int>::iterator it = lower_bound(dp.begin(), dp.end(), X.at(i));
    size_t pos = it - dp.begin();
    if (i == 0) {
      len.at(0) = (int)pos;
    } else {
      len.at(i) = max((int)pos, len.at(i - 1));
    }
    *it = X.at(i);
    value.at(i) = dp.at(len.at(i));
  }
  return make_pair(len, value);
}

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int n = 0; n < N; n++) {
    cin >> A.at(n);
  }
  auto lis0 = lis(A);
  reverse(A.begin(), A.end());
  auto lis1 = lis(A);
  int ans = 0;
  for (int k = 0; k < N - 1; k++) {
    int now = lis0.first[k] + lis1.first[N - k - 2];
    if (lis0.second[k] == lis1.second[k]) {
      now--;
    }
    ans = max(ans, now);
  }
  ans = max(ans, lis0.first[N - 1]);
  ans = max(ans, lis1.first[N - 1]);
  cout << ans << endl;
  return 0;
}
