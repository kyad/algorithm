// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  int N, M, start;
  cin >> N >> M >> start;
  vector<vector<pair<int, long long> > > graph(N);
  for (int m = 0; m < M; m++) {
    int U, V;
    long long D;
    cin >> U >> V >> D;  // U, V: 0-indexed
    graph[U].push_back(make_pair(V, D));
    //graph[V].push_back(make_pair(U, D));
  }
  // Dijkstra's algorithm (O|E|log|V|)
  const long long INF = 4e18;
  vector<long long> dist(N, INF);
  priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
  dist.at(start) = 0;
  pq.push(make_pair(0, start));
  while (!pq.empty()) {
    long long dist_min = pq.top().first;
    long long u = pq.top().second;
    pq.pop();
    if (dist_min > dist.at(u)) {
      continue;  // Garbage
    }
    for (pair<int, long long> p : graph.at(u)) {
      int v = p.first;
      long long cost = p.second;
      if (dist_min + cost < dist.at(v)) {
        dist.at(v) = dist_min + cost;
        pq.push(make_pair(dist.at(v), v));
      }
    }
  }
  for (int u = 0; u < N; u++) {
    if (dist[u] == INF) {
      cout << "INF\n";
    } else {
      cout << dist[u] << '\n';
    }
  }
  return 0;
}
