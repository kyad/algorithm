// https://atcoder.jp/contests/abc138/tasks/abc138_d
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap13/code_13_2.cpp

// Please increase stack size by `ulimit -s 1048576` before running this.
// Otherwise, segfault for N ~= 105000

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > graph;
vector<bool> seen;
vector<int> X;
vector<int> ans;

void dfs(int u, int value) {
  seen[u] = true;
  value += X[u];
  ans[u] = value;
  for (size_t i = 0; i < graph[u].size(); i++) {
    int v = graph[u][i];
    if (seen[v]) {
      continue;
    }
    dfs(v, value);
  }
  value -= X[u];
}

int main() {
  int N, Q;
  cin >> N >> Q;
  graph.resize(N);
  seen.assign(N, false);
  X.assign(N, 0);
  ans.assign(N, 0);
  for (int n = 0; n < N - 1; n++) {
    int a, b;
    cin >> a >> b;
    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }
  for (int q = 0; q < Q; q++) {
    int p, x;
    cin >> p >> x;
    X[p - 1] += x;
  }
  dfs(0, 0);
  for (int n = 0; n < N; n++) {
    cout << ans[n] << (n == N - 1 ? '\n' : ' ');
  }
  return 0;
}
