// https://atcoder.jp/contests/abc272/tasks/abc272_d

#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  map<int, int> mp;
  for (int i = 0; i <= 1000; i++) {
    mp[i * i] = i;
  }
  vector<int> di, dj;
  for (int i = 0; i <= 1000; i++) {
    int j2 = M - (i * i);
    if (mp.count(j2) > 0) {
      int j = mp[j2];
      di.push_back(i); dj.push_back(j);
      di.push_back(i); dj.push_back(-j);
      di.push_back(-i); dj.push_back(j);
      di.push_back(-i); dj.push_back(-j);
    }
  }
  assert(di.size() == dj.size());

  // Dijkstra
  const long long INF = 4e18;
  vector<vector<long long> > dist(N, vector<long long>(N, INF));
  dist[0][0] = 0;
  priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int> >, greater<tuple<long long, int, int> > > pq;
  pq.push(make_tuple(0, 0, 0));
  while (!pq.empty()) {
    long long dist_min = get<0>(pq.top());
    int dist_min_i = get<1>(pq.top());
    int dist_min_j = get<2>(pq.top());
    pq.pop();
    if (dist_min > dist[dist_min_i][dist_min_j]) {
      // garbage
      continue;
    }
    
    for (size_t k = 0; k < di.size(); k++) {
      int ni = dist_min_i + di[k];
      int nj = dist_min_j + dj[k];
      if (ni < 0 || nj < 0 || ni >= N || nj >= N) {
        continue;
      }
      long long cost = 1;
      if (dist[ni][nj] > dist_min + cost) {
        dist[ni][nj] = dist_min + cost;
        pq.push(make_tuple(dist[ni][nj], ni, nj));
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      long long now = dist[i][j];
      if (now == INF) {
        now = -1;
      }
      cout << now << (j + 1 == N ? '\n' : ' ');
    }
  }
  return 0;
}
