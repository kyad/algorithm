// https://atcoder.jp/contests/abc126/tasks/abc126_d
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap13/code_13_5.cpp

#include <iostream>
#include <vector>
using namespace std;

vector<int> color;
bool dfs(const vector<vector<int> > &graph, int v, int cur = 0) {
  color[v] = cur;
  for (size_t i = 0; i < graph[v].size(); i++) {
    int next_v = graph[v][i];
    if (color[next_v] != -1) {
      if (color[next_v] == cur) {
        return false;
      }
      continue;
    }
    if (!dfs(graph, next_v, 1 - cur)) {
      return false;
    }
  }
  return true;
}

int main() {
  int N;
  cin >> N;
  vector<vector<int> > graph(N * 2);
  for (int i = 0; i < N; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    if (w % 2 == 0) {
      graph[u - 1].push_back(u - 1 + N);
      graph[u - 1 + N].push_back(u - 1);
      graph[u - 1 + N].push_back(v - 1);
      graph[v - 1].push_back(u - 1 + N);
    } else {
      graph[u - 1].push_back(v - 1);
      graph[v - 1].push_back(u - 1);
    }
  }
  // DFS
  color.assign(N * 2, -1);
  bool is_bipartite = true;
  for (int v = 0; v < N; v++) {
    if (color[v] != -1) {
      continue;
    }
    if (!dfs(graph, v)) {
      is_bipartite = false;
    }
  }
  for (int i = 0; i < N; i++) {
    cout << color[i] << endl;
  }
  return 0;
}
