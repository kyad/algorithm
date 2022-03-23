// https://atcoder.jp/contests/dp/tasks/dp_u
// https://kyopro-friends.hatenablog.com/entry/2019/01/12/231106
// https://primenumber.hatenadiary.jp/entry/2016/12/01/000000

#include <iostream>
#include <vector>
using namespace std;

int N;
int N2;
vector<vector<int> > A;

// dp[s]: sに対する総得点の最大値
vector<long long> dp;
vector<bool> flag;

int bit(int S, int i) {
  return (S >> i) & 1;
}

long long f(int S) {
  if (flag[S]) {
    return dp[S];
  }
  // S==Tの場合
  long long ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (bit(S, i) && bit(S, j)) {
        ans += A[i][j];
      }
    }
  }
  // Sの部分集合T全体にわたるループ
  for (int T = N2 - 1; T >= 0; T--) {
    T &= S;
    // 無限ループ防止のためにT==S, T==空集合は除く
    if (T == S || T == 0) {
      continue;
    }
    int U = S ^ T;  // U = S \ T
    ans = max(ans, f(T) + f(U));
  }
  flag[S] = true;
  return dp[S] = ans;
}

int main() {
  cin >> N;
  N2 = 1<<N;
  A.resize(N, vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> A.at(i).at(j);
    }
  }
  dp.resize(N2, 0);
  flag.resize(N2, false);
  // O(N^3)
  cout << f(N2 - 1) << endl;
  return 0;
}
