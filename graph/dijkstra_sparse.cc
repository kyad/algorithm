// https://atcoder.jp/contests/abc252/tasks/abc252_e
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_4.cpp

#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<tuple<int, int, int> > > graph(N);
  for (int m = 0; m < M; m++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    graph.at(a).push_back(make_tuple(b, c, m));
    graph.at(b).push_back(make_tuple(a, c, m));
  }
  // Dijkstra's algorithm for sparse graph (O|E|log|V|)
  const long long INF = 1e18;
  vector<long long> dist(N, INF);
  vector<int> indeces(N, -1);
  dist.at(0) = 0;
  priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
  pq.push(make_pair(0, 0));
  while (!pq.empty()) {
    long long dist_min = pq.top().first;
    int dist_min_idx = pq.top().second;
    pq.pop();
    if (dist_min > dist.at(dist_min_idx)) {
      // garbage
      continue;
    }
    vector<tuple<int, int, int> > edges = graph.at(dist_min_idx);
    for (size_t i = 0; i < edges.size(); i++) {
      int v = get<0>(edges.at(i));
      int cost = get<1>(edges.at(i));
      int idx = get<2>(edges.at(i));
      if (dist.at(v) > dist_min + cost) {
        dist.at(v) = dist_min + cost;
        indeces.at(v) = idx;
        pq.push(make_pair(dist.at(v), v));
      }
    }
  }
  for (int n = 1; n < N; n++) {
    cout << (indeces.at(n) + 1) << (n == N - 1 ? '\n' : ' ');
  }
  return 0;
}
