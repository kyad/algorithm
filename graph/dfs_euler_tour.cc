// https://atcoder.jp/contests/abc213/tasks/abc213_d

#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<priority_queue<int> > graph(N);
  for (int i = 0; i < N - 1; i++) {
    int A, B;
    cin >> A >> B;
    graph[A - 1].push(B - 1);
    graph[B - 1].push(A - 1);
  }
  stack<int> todo;
  todo.push(0);
  vector<bool> visited(N, false);
  vector<int> history;
  while(!todo.empty()) {
    int v = todo.top();
    todo.pop();
    visited[v] = true;
    history.push_back(v);
    while (!graph[v].empty()) {
      int w = graph[v].top();
      graph[v].pop();
      if (!visited[w]) {
        todo.push(v);
        todo.push(w);
      }
    }
  }
  for (size_t i = 0; i < history.size(); i++) {
    cout << history[i] + 1;
    if (i == history.size() - 1) {
      cout << endl;
    } else {
      cout << ' ';
    }
  }
  return 0;
}
