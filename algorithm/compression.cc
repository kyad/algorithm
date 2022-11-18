// https://atcoder.jp/contests/abc273/tasks/abc273_f

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template<class T> void chmin(T& a, const T b) { a = min(a, b); }

// Coordinate compression
// https://github.com/atcoder/live_library/blob/master/cc.cpp
#include <algorithm>
template<typename T=int> struct CC {
  bool initialized;
  vector<T> xs;
  CC() : initialized(false) {}
  void add(T x) { xs.push_back(x); }
  void init() {  // O(Nlog(N))
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    initialized = true;
  }
  int operator()(T x) {  // 圧縮前の値から圧縮後の値を得る。O(logN)
    if (!initialized) { init(); }
    return upper_bound(xs.begin(), xs.end(), x) - xs.begin() - 1;
  }
  T operator[](int i) {  // 圧縮後の値から圧縮前の値を得る。O(1)
    if (!initialized) { init(); }
    return xs[i];
  }
  int size() {
    if (!initialized) { init(); }
    return xs.size();
  }
};

int main() {
  int N, X;
  cin >> N >> X;
  vector<int> Y(N), Z(N);
  for (int n = 0; n < N; n++) {
    cin >> Y.at(n);
  }
  for (int n = 0; n < N; n++) {
    cin >> Z.at(n);
  }
  CC cc;
  cc.add(0);
  cc.add(X);
  for (int n = 0; n < N; n++) {
    cc.add(Y[n]);
    cc.add(Z[n]);
  }
  int M = cc.size();
  vector<int> wall(M, -1);
  for (int n = 0; n < N; n++) {
    wall.at(cc(Y[n])) = n;
  }

  const long long INF = 4e18;
  vector<vector<vector<long long> > > dp(2, vector<vector<long long> >(M, vector<long long>(M, INF)));
  int s = cc(0);
  for (int k = 0; k < 2; k++) {
    dp[k][s][s] = 0;
  }

  // i番目のハンマーが[l, r]内にあるか？
  auto hammer = [&](int i, int l, int r) {
    return cc[l] <= Z[i] && Z[i] <= cc[r];
  };

  auto f = [&](int l, int r) {
    return cc[r] - cc[l];
  };

  long long ans = INF;
  int g = cc(X);
  for (int l = s; l >= 0; l--) {
    for (int r = s; r < M; r++) {
      chmin(dp[0][l][r], dp[1][l][r] + f(l, r));
      chmin(dp[1][l][r], dp[0][l][r] + f(l, r));
      // 左へ拡張する
      if (l - 1 >= 0) {
        if (wall[l - 1] == -1 || hammer(wall[l - 1], l, r)) {
          chmin(dp[0][l - 1][r], dp[0][l][r] + f(l - 1, l));
        }
      }
      // 右へ拡張する
      if (r + 1 < M) {
        if (wall[r + 1] == -1 || hammer(wall[r + 1], l, r)) {
          chmin(dp[1][l][r + 1], dp[1][l][r] + f(r, r + 1));
        }
      }
      if (l <= g && g <= r) {
        chmin(ans, dp[0][l][r]);
        chmin(ans, dp[1][l][r]);
      }
    }
  }
  if (ans == INF) {
    ans = -1;
  }
  cout << ans << endl;
  return 0;
}
