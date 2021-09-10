// https://atcoder.jp/contests/joi2008yo/tasks/joi2008yo_f
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_3.cpp

#include <iostream>
#include <vector>
using namespace std;

const int INF = 1000001;

// Dijkstra's algorithm for dense graph (O|V|^2)
vector<int> dijkstra_dense(vector<vector<pair<int, int> > > graph, int start) {
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
    }
    used[dist_min_idx] = true;
  }
  return dist;
}

int main() {
  int n, k;
  cin >> n >> k;
  vector<vector<pair<int, int> > > graph(n);
  for (int i = 0; i < k; i++) {
    int q;
    cin >> q;
    if (q == 0) {
      int a, b;
      cin >> a >> b;
      vector<int> dist = dijkstra_dense(graph, a - 1);
      cout << (dist[b - 1] < INF ? dist[b - 1] : -1) << endl;
    } else {
      int c, d, e;
      cin >> c >> d >> e;
      graph[c - 1].push_back(make_pair(d - 1, e));
      graph[d - 1].push_back(make_pair(c - 1, e));
    }
  }
  return 0;
}
