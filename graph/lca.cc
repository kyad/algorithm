// https://atcoder.jp/contests/abc438/editorial/14945

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// 木のLCA(最近共通祖先)
struct LCA {
  // 2^(K-1)個まで上がった先祖を高速に求められるようにしておく
  int K = -1;
  // parent[k][u]: uから2^k個上がった先祖
  vector<vector<int> > parent;
  // dist[u]: rootからuまでの距離
  vector<int> dist;
  // 初期化
  // 計算量: O(NlogN)
  LCA(const vector<vector<int> > &graph, int root) {
    int N = graph.size();
    // Kを求める。大き目に取っている
    K = 1;
    while ((1 << K) < N) {
      K++;
    }
    parent.resize(K, vector<int>(N, -1));
    dist.resize(N, -1);
    dist.at(root) = 0;
    // 木のDFS
    auto dfs = [&](auto dfs, int u, int p) -> void {
      parent.at(0).at(u) = p;
      for (int v: graph.at(u)) {
        if (v != p) {
          dist.at(v) = dist.at(u) + 1;
          dfs(dfs, v, u);
        }
      }
    };
    dfs(dfs, root, -1);
    // 先祖を求める
    for (int k = 1; k < K; k++) {
      for (int u = 0; u < N; u++) {
        int v = parent.at(k - 1).at(u);
        if (v >= 0) {
          parent.at(k).at(u) = parent.at(k - 1).at(v);
        } else {
          parent.at(k).at(u) = -1;
        }
      }
    }
  }
  // uとvの最近共通先祖を求める
  // 計算量: O(logN)
  int query(int u, int v) {
    // uの方がvより深いとする
    if (dist.at(u) < dist.at(v)) {
      swap(u, v);
    }
    // uをvと同じ高さに合わせたものをu1とする
    for (int k = 0; k < K; k++) {
      if ((dist.at(u) - dist.at(v)) >> k & 1) {
        u = parent.at(k).at(u);
      }
    }
    // u1とvの最近共通先祖を求める
    if (u == v) {
      return u;
    }
    // 二分探索
    for (int k = K - 1; k >= 0; k--) {
      if (parent.at(k).at(u) != parent.at(k).at(v)) {
        u = parent.at(k).at(u);
        v = parent.at(k).at(v);
      }
    }
    return parent.at(0).at(u);
  }
  // uとvの距離を求める
  // 計算量: O(logN)
  int query_dist(int u, int v) {
    int a = query(u, v);
    int ans = dist.at(u) + dist.at(v) - 2 * dist.at(a);
    return ans;
  }
  // xがuとvのパス上に存在するか(端点u, v上も含む)
  // 計算量: O(logN)
  bool on_path(int u, int v, int x) {
    int uv = query_dist(u, v);
    int ux = query_dist(u, x);
    int vx = query_dist(v, x);
    bool ans = ux + vx == uv;
    return ans;
  }
};

int main() {
  int N;
  cin >> N;
  vector<vector<int> > graph(N);
  for (int j = 0; j < N - 1; j++) {
    int U, V;
    cin >> U >> V;
    graph.at(U).push_back(V);
    graph.at(V).push_back(U);
  }

  // dp[u]: 0を頂点とした時u以下の頂点数
  vector<int> dp(N, 0);
  auto dfs = [&](auto dfs, int u, int parent) -> int {
    dp.at(u) = 1;
    for (int v: graph.at(u)) {
      if (v != parent) {
        dp.at(u) += dfs(dfs, v, u);
      }
    }
    return dp.at(u);
  };
  dfs(dfs, 0, -1);

  // 0から1のパス上にある点のうち、0に一番近い点aを求める
  int a = -1;
  LCA lca(graph, 0);
  for (int u = 0; u < N; u++) {
    if (lca.on_path(0, 1, u) && lca.dist.at(u) == 1) {
      a = u;
      break;
    }
  }
  assert(a >= 0);

  // C[k]: 0, 1, ..., kを全て通るパスの個数。C[N]=0
  vector<long long> C(N + 1, 0);
  // C[0]は特別
  auto f = [&](int c) -> long long {
    long long ans = (long long)c * (c + 1) / 2;
    return ans;
  };
  C.at(0) = f(N);
  for (int u: graph.at(0)) {
    C.at(0) -= f(dp.at(u));
  }
  int l = 0, r = 0;  // パス
  for (int k = 1; k < N; k++) {
    // k-1からkへの遷移
    if (lca.on_path(k, r, l)) {
      l = k;
    } else if (lca.on_path(l, r, k)) {
    } else if (lca.on_path(l, k, r)) {
      r = k;
    } else {
      // 0, 1, ..., kが一直線上に無い
      break;
    }
    // lが小さいようにする
    if (l > r) {
      swap(l, r);
    }
    if (l == 0) {  // 特別扱い
      C.at(k) = (long long)(N - dp.at(a)) * dp.at(r);
    } else {
      C.at(k) = (long long)dp.at(l) * dp.at(r);
    }
  }
  long long ans = 0;
  for (int f = 1; f <= N; f++) {
    long long count = C.at(f - 1) - C.at(f);
    long long now = count * f;
    ans += now;
  }
  cout << ans << endl;
  return 0;
}
