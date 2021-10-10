// https://atcoder.jp/contests/abc222/tasks/abc222_e

#include <iostream>
#include <vector>
using namespace std;

// On tree, search the shortest path from s to t by DFS. O(N)
vector<vector<pair<int, int> > > graph;
vector<int> count;
bool dfs_tree(int s, int parent, int t) {
  if (s == t) {
    return true;
  }
  for (size_t i = 0; i < graph[s].size(); i++) {
    int v = graph[s][i].first;
    int edge_id = graph[s][i].second;
    if (v == parent) {
      continue;
    }
    if (dfs_tree(v, s, t)) {
      count[edge_id]++;
      return true;
    }
  }
  return false;
}

int main() {
  int N, M, K;
  cin >> N >> M >> K;
  vector<int> A(M);
  for (int m = 0; m < M; m++) {
    cin >> A.at(m);
    A.at(m)--;
  }
  graph.resize(N);
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u - 1].push_back(make_pair(v - 1, i));
    graph[v - 1].push_back(make_pair(u - 1, i));
  }
  count.resize(N - 1);
  for (int m = 0; m < M - 1; m++) {
    dfs_tree(A.at(m), -1, A.at(m + 1));
  }
  const unsigned int MOD = 998244353;
  vector<vector<unsigned int> > dp(N - 1, vector<unsigned int>(200001, 0));
  const int OFS = 100000;
  for (int i = 0; i < N - 1; i++) {
    if (i == 0) {
      dp[0][count[0] + OFS]++;
      dp[0][-count[0] + OFS]++;
    } else {
      for (int j = -100000; j <= 100000; j++) {
        if (j + count[i] <= 100000) {
          dp[i][j + count[i] + OFS] += dp[i - 1][j + OFS];
          dp[i][j + count[i] + OFS] %= MOD;
        }
        if (j - count[i] >= -100000) {
          dp[i][j - count[i] + OFS] += dp[i - 1][j + OFS];
          dp[i][j - count[i] + OFS] %= MOD;
        }
      }
    }
  }
  cout << dp[N - 2][K + OFS] << endl;
  return 0;
}
