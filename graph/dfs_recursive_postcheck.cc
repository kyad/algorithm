// https://atcoder.jp/contests/abc280/tasks/abc280_f
// DFSで、既に行ったノードかを再帰後にチェックする場合の実装。

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<vector<pair<int, int> > > graph(N);
  for (int m = 0; m < M; m++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--; b--;
    graph[a].push_back(make_pair(b, c));
    graph[b].push_back(make_pair(a, -c));
  }

  vector<int> cid(N, -1);  // >=0なら連結成分ID。-1なら探索が完了していない。
  vector<long long> po(N, 0);  // ポテンシャル
  int nc = 0;  // 今の連結成分ID
  vector<bool> inf;  // その連結成分IDが、ポイントを無限大にできるサイクルを持っているか。
  auto dfs = [&](auto dfs, int u, long long npo) -> void {
    if (cid[u] >= 0) {  // 既に行ったノードである場合。サイクルを検出した場合。
      if (po[u] != npo) {  // ポイントを無限大にできるサイクルである条件。
        inf[nc] = true;
      }
      return;
    }
    cid[u] = nc;
    po[u] = npo;
    for (auto [v, c] : graph[u]) {
      dfs(dfs, v, po[u] + c);
    }
  };
  for (int u = 0; u < N; u++) {
    if (cid[u] >= 0) {
      continue;
    }
    inf.push_back(false);  // 連結成分ID=ncはfalseで初期化する。
    dfs(dfs, u, 0);
    nc++;
  }
  for (int q = 0; q < Q; q++) {
    int X, Y;
    cin >> X >> Y;
    X--; Y--;
    // XとYが非連結な時は行けない
    if (cid[X] != cid[Y]) {
      cout << "nan" << '\n';
      continue;
    }
    // XとYが連結かつポイントを無限大にできるサイクルがある場合
    if (inf[cid[X]]) {
      cout << "inf" << '\n';
      continue;
    }
    // XとYが連結かつポイントを無限大にできるサイクルがない場合
    long long ans = po[Y] - po[X];
    cout << ans << '\n';
  }
  return 0;
}
