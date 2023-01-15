// https://atcoder.jp/contests/abc285/tasks/abc285_d

#include <cassert>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
using namespace std;

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
  vector<string> S(N), T(N);
  for (int n = 0; n < N; n++) {
    cin >> S.at(n) >> T.at(n);
  }
  map<string, int> mp;
  int M = 0;
  for (int n = 0; n < N; n++) {
    if (mp.count(S[n]) == 0) {
      mp[S[n]] = M;
      M++;
    }
    if (mp.count(T[n]) == 0) {
      mp[T[n]] = M;
      M++;
    }
  }

  vector<vector<int> > graph(M);
  for (int n = 0; n < N; n++) {
    graph[mp[S[n]]].push_back(mp[T[n]]);
  }

  // Topological sort
  seen.assign(M, false);
  finished.assign(M, false);
  order.clear();
  for (int v = 0; v < M; v++) {
    if (seen[v]) {
      continue;
    }
    dfs(graph, v);
  }
  if (cycle_v >= 0) {  // Have cycle
    cout << "No" << endl;
    return 0;
  }
  cout << "Yes" << endl;
  return 0;
}
