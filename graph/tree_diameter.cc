// https://atcoder.jp/contests/typical90/tasks/typical90_c

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// BFS
// Augments
//   graph: tree, 0-indexed
// Returns
//   dist
vector<int> bfs(const vector<vector<int> > &graph, int s) {
  int N = (int)graph.size();
  queue<int> todo;
  vector<int> dist(N, -1);
  dist[s] = 0;
  todo.push(s);
  while (!todo.empty()) {
    int u = todo.front();
    todo.pop();
    for (size_t i = 0; i < graph[u].size(); i++) {
      int v = graph[u][i];
      if (dist[v] < 0) {
	dist[v] = dist[u] + 1;
	todo.push(v);
      }
    }
  }
  return dist;
}

// Diameter of tree
// Augments
//   graph: tree, 0-indexed
int tree_diameter(const vector<vector<int> > &graph) {
  vector<int> dist0 = bfs(graph, 0);
  vector<int>::iterator it = max_element(dist0.begin(), dist0.end());
  int pos = it - dist0.begin();
  vector<int> dist1 = bfs(graph, pos);
  return *max_element(dist1.begin(), dist1.end());
}

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
  int E = tree_diameter(graph);
  cout << (E + 1) << endl;
  return 0;
}
