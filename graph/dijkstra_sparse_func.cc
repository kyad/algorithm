// https://atcoder.jp/contests/typical90/tasks/typical90_m
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_4.cpp

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const long long INF = 4e18;

struct Edge {
  Edge(int _v, long long _w) : v(_v), w(_w) {}
  int v;  // node;
  long long w;  // weight;
}; 

// Dijkstra's algorithm for sparse graph (O|E|log|V|)
vector<long long> dijkstra(const vector<vector<Edge> > &graph, int start) {
  size_t N = graph.size();
  vector<long long> dist(N, INF);
  dist.at(start) = 0;
  priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
  pq.push(make_pair(0, start));
  while (!pq.empty()) {
    long long dist_min = pq.top().first;
    int dist_min_idx = pq.top().second;
    pq.pop();
    if (dist_min > dist.at(dist_min_idx)) {
      // garbage
      continue;
    }
    vector<Edge> edges = graph.at(dist_min_idx);
    for (size_t i = 0; i < edges.size(); i++) {
      int v = edges.at(i).v;
      int cost = edges.at(i).w;
      if (dist.at(v) > dist_min + cost) {
        dist.at(v) = dist_min + cost;
        pq.push(make_pair(dist.at(v), v));
      }
    }
  }
  return dist;
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<Edge> > graph(N);
  for (int m = 0; m < M; m++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    graph.at(a).push_back(Edge(b, c));
    graph.at(b).push_back(Edge(a, c));
  }
  vector<long long> dist0 = dijkstra(graph, 0);
  vector<long long> dist1 = dijkstra(graph, N - 1);
  for (int n = 0; n < N; n++) {
    long long ans = dist0.at(n) + dist1.at(n);
    cout << ans << endl;
  }
  return 0;
}
