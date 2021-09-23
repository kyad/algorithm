// https://atcoder.jp/contests/joi2016yo/tasks/joi2016yo_e
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_4.cpp

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  int N, M, K, S;
  cin >> N >> M >> K >> S;
  int P, Q;
  cin >> P >> Q;
  vector<int> C(K);
  for (int k = 0; k < K; k++) {
    cin >> C.at(k);
    C.at(k)--;
  }
  vector<int> A(M), B(M);
  for (int m = 0; m < M; m++) {
    cin >> A.at(m) >> B.at(m);
    A.at(m)--;
    B.at(m)--;
  }
  vector<vector<int> > graph1(N);
  for (int m = 0; m < M; m++) {
    graph1.at(A.at(m)).push_back(B.at(m));
    graph1.at(B.at(m)).push_back(A.at(m));
  }
  // BFS
  queue<int> todo;
  vector<int> dist1(N, -1);
  for (int k = 0; k < K; k++) {
    todo.push(C.at(k));
    dist1.at(C.at(k)) = 0;
  }
  while (!todo.empty()) {
    int v = todo.front();
    todo.pop();
    for (size_t i = 0; i < graph1.at(v).size(); i++) {
      int nv = graph1.at(v).at(i);
      if (dist1.at(nv) >= 0) {
        continue;
      }
      dist1.at(nv) = dist1.at(v) + 1;
      todo.push(nv);
    }
  }
  vector<vector<pair<int, int> > > graph2(N);
  for (int m = 0; m < M; m++) {
    int a = A.at(m);
    int b = B.at(m);
    // a --> b
    if (b == 0) {
    } else if (b == N - 1) {
      graph2.at(a).push_back(make_pair(b, 0));
    } else if (dist1.at(b) > S) {
      // danger
      graph2.at(a).push_back(make_pair(b, P));
    } else if (dist1.at(b) > 0) {
      // safe
      graph2.at(a).push_back(make_pair(b, Q));
    }
    // b --> a
    if (a == 0) {
    } else if (a == N - 1) {
      graph2.at(b).push_back(make_pair(a, 0));
    } else if (dist1.at(a) > S) {
      // danger
      graph2.at(b).push_back(make_pair(a, P));
    } else if (dist1.at(a) > 0) {
      // safe
      graph2.at(b).push_back(make_pair(a, Q));
    }
  }
  // Dijkstra's algorithm for sparse graph (O|E|log|V|)
  const long long INF = (long long)100000 * 200000 + 1;
  vector<long long> dist2(N, INF);
  dist2.at(0) = 0;
  priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
  pq.push(make_pair(0, 0));
  while (!pq.empty()) {
    long long dist_min = pq.top().first;
    int dist_min_idx = pq.top().second;
    pq.pop();
    if (dist_min > dist2.at(dist_min_idx)) {
      // garbage
      continue;
    }
    vector<pair<int, int> > edges = graph2.at(dist_min_idx);
    for (size_t i = 0; i < edges.size(); i++) {
      int v = edges.at(i).first;
      int cost = edges.at(i).second;
      if (dist2.at(v) > dist_min + cost) {
        dist2.at(v) = dist_min + cost;
        pq.push(make_pair(dist2.at(v), v));
      }
    }
  }
  cout << dist2.at(N - 1) << endl;
  return 0;
}
