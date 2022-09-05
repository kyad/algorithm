// https://atcoder.jp/contests/abc267/tasks/abc267_f

#include <deque>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<vector<int> > graph(N);
  for (int n = 0; n < N - 1; n++) {
    int A, B;
    cin >> A >> B;
    A--; B--;
    graph[A].push_back(B);
    graph[B].push_back(A);
  }
  int Q;
  cin >> Q;
  vector<vector<pair<int, int> > > qs(N);
  for (int q = 0; q < Q; q++) {
    int U, K;
    cin >> U >> K;
    U--;
    qs[U].push_back(make_pair(q, K));
  }

  // Diameter
  auto dfs_farthest = [&](auto dfs_farthest, int u, int d = 0, int parent = -1) -> pair<int, int> {
    pair<int, int> ans = make_pair(d, u);
    for (int v : graph[u]) {
      if (v == parent) {
        continue;
      }
      ans = max(ans, dfs_farthest(dfs_farthest, v, d + 1, u));
    }
    return ans;
  };
  int a = dfs_farthest(dfs_farthest, 0).second;
  int b = dfs_farthest(dfs_farthest, a).second;

  // Level Ancestor Probrem
  vector<int> ans(Q, -1);
  deque<int> dq;
  auto dfs = [&](auto dfs, int u, int parent = -1) -> void {
    dq.push_front(u);
    for (auto [q, K] : qs[u]) {
      if (K < dq.size()) {
        ans[q] = dq[K] + 1;
      }
    }
    for (int v : graph[u]) {
      if (v == parent) {
        continue;
      }
      dfs(dfs, v, u);
    }
    dq.pop_front();
  };
  dfs(dfs, a);
  dfs(dfs, b);

  for (int q = 0; q < Q; q++) {
    cout << ans[q] << endl;
  }
  return 0;
}
