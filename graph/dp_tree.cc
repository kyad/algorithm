// https://atcoder.jp/contests/abc149/tasks/abc149_f

#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
using namespace std;

// Solve ax = 1 mod m  (m != prime is OK), O(log m)
// Solve ay = b mod m --> y = b * x mod m
long long modinv(long long a, long long m) {
  long long b = m, u = 1, v = 0;
  while (b) {
    long long t = a / b;
    a -= t * b;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  u %= m;
  if (u < 0) {
    u += m;
  }
  return u;
}

// m^n, O(log n)
int power(int m, int n, int mod) {
  long long a = m;
  long long ans = 1;
  while (n > 0) {
    if ((n & 1) == 1) {
      ans *= a;
      ans %= mod;
    }
    a *= a;
    a %= mod;
    n >>= 1;
  }
  return ans;
}

// get<0>(graph[u][i]) == v: Node
// get<1>(graph[u][i]): uから見てv側にあるすべてのノードの数
// get<2>(graph[u][i]) == j: graph[v]における反対方向の枝のインディックス。graph[u][i]とgraph[v][j]は反対方向の枝
vector<vector<tuple<int, int, int> > > graph;
vector<bool> visited;
int dfs(int u, int parent) {
  visited[u] = true;
  int ans = 1;
  for (size_t i = 0; i < graph[u].size(); i++) {
    int v = get<0>(graph[u][i]);
    if (v == parent) {
      continue;
    }
    int temp = dfs(v, u);
    get<1>(graph[u][i]) += temp;
    ans += temp;
  }
  return ans;
}

int main() {
  int N;
  cin >> N;
  graph.resize(N);
  vector<int> deg(N, 0);
  for (int n = 0; n < N - 1; n++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    size_t sa = graph[a].size();
    size_t sb = graph[b].size();
    graph[a].push_back(make_tuple(b, 0, sb));
    graph[b].push_back(make_tuple(a, 0, sa));
    deg[a]++;
    deg[b]++;
  }
  // DFSで、get<1>(graph[u][i])をO(N)で計算する
  int start = -1;
  for (int n = 0; n < N; n++) {
    if (deg[n] == 1) {
      start = n;
      break;
    }
  }
  visited.assign(N, false);
  dfs(start, -1);
  for (int n = 0; n < N; n++) {
    for (size_t i = 0; i < graph[n].size(); i++) {
      if (get<1>(graph[n][i]) == 0) {
        int v = get<0>(graph[n][i]);
        size_t j = get<2>(graph[n][i]);
        get<1>(graph[n][i]) = N - get<1>(graph[v][j]);
      }
    }
  }
  const int MOD = 1000000007;
  long long ans = 0;
  for (int n = 0; n < N; n++) {
    if (graph[n].size() > 1) {
      long long sum = 0;
      long long mul = 1;
      for (size_t i = 0; i < graph[n].size(); i++) {
        int num = get<1>(graph[n][i]);
        int temp = power(2, num, MOD);
        sum += temp;
        sum %= MOD;
        sum += (MOD - 1);
        sum %= MOD;
        mul *= temp;
        mul %= MOD;
      }
      ans += mul;
      ans %= MOD;
      ans += MOD;
      ans -= sum;
      ans %= MOD;
      ans += (MOD - 1);
      ans %= MOD;
    }
  }
  long long inv = modinv(power(2, N, MOD), MOD);
  ans *= inv;
  ans %= MOD;
  cout << ans << endl;
  return 0;
}
