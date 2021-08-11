// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_3.cpp

#include <bits/stdc++.h>
using namespace std;

// Dijkstra's algorithm for dense graph (O|V|^2)
vector<int> dijkstra_dense(vector<vector<pair<int, int> > > graph, int start) {
  const int INF = 1000000000;
  int N = (int)graph.size();
  vector<bool> used(N, false);
  vector<int> dist(N, INF);
  dist[start] = 0;
  for (int i = 0; i < N; i++) {
    int dist_min = INF;
    int dist_min_idx = -1;
    for (int j = 0; j < N; j++) {
      if (!used[j] && dist[j] < dist_min) {
        dist_min = dist[j];
        dist_min_idx = j;
      }
    }
    if (dist_min_idx == -1) {
      break;
    }
    for (size_t e = 0; e < graph[dist_min_idx].size(); e++) {
      if (dist[graph[dist_min_idx][e].first] > dist_min + graph[dist_min_idx][e].second) {
        dist[graph[dist_min_idx][e].first] = dist_min + graph[dist_min_idx][e].second;
      }
      used[dist_in_idx] = 0;
    }
  }
  return dist;
}
