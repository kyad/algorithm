// https://atcoder.jp/contests/typical90/tasks/typical90_am

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/**
 * 全方位木DP。(Rerooting)
 * uを根と思って木DPした時の根のDP値dp_top[u]を全て計算する。
 * 計算量はO(N)。
 */
using Data = pair<int, long long>;  // DPの型●
const Data IDENTITY = make_pair(0, 0); // Dataの単位元●
// Dataの二項演算。dp_u = f(dp_u, dp_v)する。結合則が成り立つこと。●
void dp_merge(Data &dp_u, const Data &dp_v) {
  dp_u.first += dp_v.first;
  dp_u.second += dp_v.second;
}
// DPの遷移式。dp_u = f(dp_u, dp_v)とする。●
void dp_apply(Data &dp_u, const Data &dp_v) {
  dp_u.first += dp_v.first;
  dp_u.second += (dp_v.first + dp_v.second);
}

vector<vector<Data> > graph;

// iを根と思った時、iからスタートした時の最大値
vector<pair<int, long long> > dp;
void dfs0(int u, int parent) {
  dp[u] = make_pair(1, 0);  // 葉の値。●
  for (auto [v, w] : graph[u]) {
    if (v == parent) {
      continue;
    }
    dfs0(v, u);
    dp_apply(dp[u], dp[v]);
  }
}
    
vector<Data> dp_top;  // dp_top[u]は、uを根と思って木DPした時のdp[u]の値。これを高速に計算するのが目標。
void dfs1(int u, int parent) {
  int K = graph[u].size();
  // uを根と思って木DPした時のdp[u](dp_top[u])を計算する。
  dp_top[u] = make_pair(1, 0);  // 葉の値。●
  for (int k = 0; k < K; k++) {
    auto [v, w] = graph[u][k];
    dp_apply(dp_top[u], dp[v]);
  }
  // Rerootingの準備として、子のDP値の累積和を左右から計算する。
  vector<Data> left(K), right(K);  // 子のDP値の累積和。
  for (int k = 0; k < K; k++) {
    auto [v, w] = graph[u][k];
    left[k] = right[k] = dp[v];  // 初期値は子の値。
  }
  for (int k = 1; k < K; k++) {  // 左からの累積和を計算する。
    dp_merge(left[k], left[k - 1]);
  }
  for (int k = K - 2; k >= 0; k--) {  // 右からの累積和を計算する。
    dp_merge(right[k], right[k + 1]);
  }
  for (int k = 0; k < K; k++) {
    auto [v, w] = graph[u][k];
    if (v == parent) {
      continue;
    }
    // Rerooting
    // Update dp[u]
    dp[u] = make_pair(1, 0);  // 葉の値。dp_topではない。●
    if (k >= 1) {  // 左からの累積和でまとめて更新する。
      dp_apply(dp[u], left[k - 1]);  // dp_topではない。
    }
    if (k <= K - 2) {  // 右からの累積和でまとめて更新する。
      dp_apply(dp[u], right[k + 1]);  // dp_topではない。
    }
    // Update dp[v]
    dfs1(v, u);
  }
}

int main() {
  int N;
  cin >> N;
  graph.resize(N);
  dp.resize(N);
  dp_top.resize(N);
  for (int n = 0; n < N - 1; n++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    graph[a].push_back(make_pair(b, 1));
    graph[b].push_back(make_pair(a, 1));
  }
  dfs0(0, -1);  // Rerootingの前計算として、0を根とした木DPをする。
  dfs1(0, -1);  // Rerootingを実行する。
  long long ans = 0;
  for (int n = 0; n < N; n++) {
    ans += dp_top.at(n).second;
  }
  ans /= 2;
  cout << ans << endl;
  return 0;
}
