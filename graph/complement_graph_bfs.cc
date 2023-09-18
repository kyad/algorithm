// https://www.youtube.com/watch?v=26jzAnxw-S4&t=7868s
// 補グラフのBFS

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;
// modint
#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;
ostream& operator<<(ostream& os, const mint &v) {
  os << v.val();
  return os;
}

int main() {
  int N, M;
  cin >> N >> M;
  // 補グラフのBFS
  vector<unordered_set<int> > graph(N);
  for (int m = 0; m < M; m++) {
    int U, V;
    cin >> U >> V;
    U--; V--;
    graph[U].insert(V);
    graph[V].insert(U);
  }
  // 距離が未確定の頂点集合
  unordered_set<int> S;
  for (int i = 0; i < N; i++) {
    S.insert(i);
  }
  // BFS
  int s = 0;  // 探索開始ノード
  S.erase(s);
  queue<int> todo;
  vector<int> dist(N, -1);
  dist.at(s) = 0;
  todo.push(s);
  while (!todo.empty()) {
    int u = todo.front();
    todo.pop();
    vector<int> del;
    for (int v : S) {  // 未確定の頂点を全て調べる
      if (graph.at(u).count(v) == 0) {  // graphに入っていない時==補グラフではつながっている時
        dist.at(v) = dist.at(u) + 1;
        del.push_back(v);
        todo.push(v);
      }
    }
    for (int v : del) {
      S.erase(v);
    }
  }

  if (dist.at(N - 1) == -1) {
    cout << -1 << endl;
    return 0;
  }

  // 後半
  vector<unordered_set<int> > vs(N);  // vs[d]: 頂点0からの距離がdの頂点集合
  for (int u = 0; u < N; u++) {
    if (dist[u] >= 0) {
      vs[dist[u]].insert(u);
    }
  }
  vector<mint> dp(N);  // dp[u]: 頂点0からのuへの最短パスの個数
  dp[0] = 1;
  for (int d = 1; d <= N - 1; d++) {
    mint sum = 0;
    for (int u : vs[d - 1]) {
      sum += dp[u];
    }
    for (int u : vs[d]) {
      dp[u] += sum;
      for (int v : graph[u]) {
        if (vs[d - 1].count(v)) {  // もし補グラフにv->uが存在していなければ
          dp[u] -= dp[v];
        }
      }
    }
  }
  mint ans = dp[N - 1];
  cout << ans << endl;
  return 0;
}
