// https://atcoder.jp/contests/abc010/tasks/abc010_4
// https://drken1215.hatenablog.com/entry/2021/08/04/155100
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
  int N, G, E;
  cin >> N >> G >> E;
  Graph graph(N + 1);
  for (int g = 0; g < G; g++) {
    int p;
    cin >> p;
    graph.addedge(p, N, 1);
    graph.addedge(N, p, 1);
  }
  for (int e = 0; e < E; e++) {
    int a, b;
    cin >> a >> b;
    graph.addedge(a, b, 1);
    graph.addedge(b, a, 1);
  }
  FordFulkerson ff;
  cout << ff.solve(graph, 0, N) << endl;
  return 0;
}
