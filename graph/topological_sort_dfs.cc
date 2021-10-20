// https://atcoder.jp/contests/abc139/tasks/abc139_e
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap13/code_13_6.cpp
// https://qiita.com/drken/items/a803d4fc4a727e02f7ba

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

#define IDX(i, j) (((N) * (i) - (i) * ((i) + 1) / 2 + (j) - (i) - 1))

// Topological sort & Cycle detection
vector<bool> seen, finished;
vector<int> order;
int cycle_v = -1;
stack<int> history;
void dfs(const vector<vector<int> > &graph, int v) {
  seen[v] = true;
  history.push(v);
  for (size_t i = 0; i < graph[v].size(); i++) {
    if (finished[graph[v][i]]) {
      continue;
    } else if (seen[graph[v][i]]) {  // Detect cycle
      cycle_v = graph[v][i];
      return;
    }
    dfs(graph, graph[v][i]);
  }
  order.push_back(v);
  history.pop();
  finished[v] = true;
}

int main() {
  int N;
  cin >> N;
  vector<vector<int> > A(N, vector<int>(N - 1));
  for (int n = 0; n < N; n++) {
    for (int m = 0; m < N - 1; m++) {
      cin >> A[n][m];
      A[n][m]--;
    }
  }
  vector<vector<int> > graph(N * (N - 1) / 2);
  for (int n = 0; n < N; n++) {
    for (int m = 0; m < N - 2; m++)  {
      int a = min(n, A[n][m]);
      int b = max(n, A[n][m]);
      int c = min(n, A[n][m + 1]);
      int d = max(n, A[n][m + 1]);
      graph[IDX(a, b)].push_back(IDX(c, d));
    }
  }
  // Topological sort
  seen.assign(N * (N - 1) / 2, false);
  finished.assign(N * (N - 1) / 2, false);
  order.clear();
  for (int v = 0; v < N * (N - 1) / 2; v++) {
    if (seen[v]) {
      continue;
    }
    dfs(graph, v);
  }
  if (cycle_v >= 0) {  // Have cycle
    cout << -1 << endl;
    return 0;
  }
  // Compute longest path
  vector<int> dist(N * (N - 1) / 2, 0);
  for (size_t i = 0; i < order.size(); i++) {
    for (size_t j = 0; j < graph[order[i]].size(); j++) {
      dist[order[i]] = max(dist[order[i]], dist[graph[order[i]][j]] + 1);
    }
  }
  cout << *max_element(dist.begin(), dist.end()) + 1 << endl;
  return 0;
}
