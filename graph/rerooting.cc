// https://atcoder.jp/contests/abc222/tasks/abc222_f

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<pair<int, int> > > graph;
vector<int> D;

// iを根と思った時、iからスタートした時の最大値
vector<long long> dp;
void dfs0(int u, int parent) {
  dp[u] = 0;
  for (auto [v, w] : graph[u]) {
    if (v == parent) {
      continue;
    }
    dfs0(v, u);
    dp[u] = max({dp[u], (long long)D[v] + w, dp[v] + w});
  }
}
    
vector<long long> ans;
void dfs1(int u, int parent) {
  int K = graph[u].size();
  ans[u] = 0;
  for (int k = 0; k < K; k++) {
    auto [v, w] = graph[u][k];
    ans[u] = max({ans[u], (long long)D[v] + w, dp[v] + w});
  }
  vector<long long> left(K), right(K);
  for (int k = 0; k < K; k++) {
    auto [v, w] = graph[u][k];
    left[k] = right[k] = max((long long)D[v] + w, dp[v] + w);
  }
  for (int k = 1; k < K; k++) {
    left[k] = max(left[k], left[k - 1]);
  }
  for (int k = K - 2; k >= 0; k--) {
    right[k] = max(right[k], right[k + 1]);
  }
  for (int k = 0; k < K; k++) {
    auto [v, w] = graph[u][k];
    if (v == parent) {
      continue;
    }
    // Rerooting
    // Update dp[u]
    dp[u] = 0;
    if (k >= 1) {
      dp[u] = max(dp[u], left[k - 1]);
    }
    if (k <= K - 2) {
      dp[u] = max(dp[u], right[k + 1]);
    }
    // Update dp[v]
    dfs1(v, u);
  }
}

int main() {
  int N;
  cin >> N;
  graph.resize(N);
  D.resize(N);
  dp.resize(N);
  ans.resize(N);
  for (int n = 0; n < N - 1; n++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--; b--;
    graph[a].push_back(make_pair(b, c));
    graph[b].push_back(make_pair(a, c));
  }
  for (int n = 0; n < N; n++) {
    cin >> D.at(n);
  }
  dfs0(0, -1);
  dfs1(0, -1);
  for (int n = 0; n < N; n++) {
    cout << ans.at(n) << endl;
  }
  return 0;
}
