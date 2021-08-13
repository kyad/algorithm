// https://atcoder.jp/contests/soundhound2018/tasks/soundhound2018_c
// https://drken1215.hatenablog.com/entry/2019/06/17/221400
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap16/code_16_1.cpp

#include <iostream>
#include <vector>
using namespace std;

// Ford-Fulkerson O(F|E|)
struct Edge {
  int rev, from, to, cap;
  Edge (int r, int f, int t, int c) : rev(r), from(f), to(t), cap(c) {}
};
ostream& operator<<(ostream& stream, const Edge &e) {
  stream << "Edge from=" << e.from << " to=" << e.to << " cap=" << e.cap << " rev=" << e.rev;
  return stream;
}

struct Graph {
  vector<vector<Edge> > list;
  Graph(int N = 0) : list(N) {}
  size_t size() const {
    return list.size();
  }
  vector<Edge> &operator [] (int i) {
    return list[i];
  }
  Edge& redge(const Edge &e) {
    return list[e.to][e.rev];
  }
  void run_flow(Edge &e, int f) {
    e.cap -= f;
    redge(e).cap += f;
  }
  void addedge(int from, int to, int cap) {
    int fromrev = (int)list[from].size();
    int torev = (int)list[to].size();
    list[from].push_back(Edge(torev, from, to, cap));
    list[to].push_back(Edge(fromrev, to, from, 0));
  }
};
ostream& operator<<(ostream& stream, const Graph &graph) {
  stream << "Graph" << endl;
  for (size_t i = 0; i < graph.size(); i++) {
    for (size_t j = 0; j < graph.list[i].size(); j++) {
      stream << " " << graph.list[i][j] << endl;
    }
  }
  return stream;
}

struct FordFulkerson {
  static const int INF = 1 << 30;
  vector<int> seen;
  FordFulkerson() {}
  int fodfs(Graph &G, int v, int t, int f) {
    if (v == t) {
      return f;
    }
    seen[v] = 1;
    for (size_t i = 0; i < G[v].size(); i++) {
      Edge& e = G[v][i];
      if (seen[e.to]) {
        continue;
      }
      if (e.cap == 0) {
        continue;
      }
      int flow = fodfs(G, e.to, t, min(f, e.cap));
      if (flow == 0) {
        continue;
      }
      G.run_flow(e, flow);
      return flow;
    }
    return 0;
  }
  int solve(Graph &G, int s, int t) {
    int res = 0;
    while (true) {
      seen.assign((int)G.size(), 0);
      int flow = fodfs(G, s, t, INF);
      if (flow == 0) {
        return res;
      }
      res += flow;
    }
    return 0;
  }
};


int main() {
  int r, c;
  cin >> r >> c;
  vector<string> C(r);
  for (int y = 0; y < r; y++) {
    cin >> C[y];
  }
  int V = r * c;
  Graph graph(r * c + 2);
  for (int y = 0; y < r; y++) {
    for (int x = 0; x < c; x++) {
      int left = y * c + x;
      if (C[y][x] == '*') {
        V--;
        continue;
      }
      if ((y + x) % 2 == 1) {
        continue;
      }
      const int dy[4] = {-1, 0, 1, 0};
      const int dx[4] = {0, -1, 0, 1};
      for (int k = 0; k < 4; k++) {
        int ny = y + dy[k];
        int nx = x + dx[k];
        if (0 <= ny && ny < r && 0 <= nx && nx < c) {
          if (C[ny][nx] == '*') {
            continue;
          }
          int right = ny * c + nx;
          graph.addedge(left, right, 1);
        }
      }
    }
  }
  // Maximum independent set problem for bipartite graph
  // --> Maximum matching problem for bipartite graph
  // --> Maximum flow problem for bipartite graph
  // Add super node
  int start = r * c;
  int end = r * c + 1;
  for (int y = 0; y < r; y++) {
    for (int x = 0; x < c; x++) {
      if ((y + x) % 2 == 0) {
        graph.addedge(start, y * c + x, 1);
        graph.addedge(y * c + x, start, 1);
      } else {
        graph.addedge(y * c + x, end, 1);
        graph.addedge(end, y * c + x, 1);
      }
    }
  }
  // Solve maximum flow problem
  FordFulkerson ff;
  int max_matching = ff.solve(graph, start, end);
  cout << V - max_matching << endl;
  return 0;
}
