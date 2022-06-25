#include <iostream>
#include <vector>
using namespace std;

// Returns ceil(a / b)
template<typename T> T ceildiv(T a, T b) {
  return (a + (b - 1)) / b;
}

int main() {
  const long long INF = 1e18;
  int N;
  cin >> N;
  vector<long long> X(N), Y(N), P(N);
  for (int n = 0; n < N; n++) {
    cin >> X.at(n) >> Y.at(n) >> P.at(n);
  }
  vector<vector<long long> > dist(N, vector<long long>(N, INF));
  for (int n = 0; n < N; n++) {
    dist[n][n] = 0;
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      long long m = abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
      dist[i][j] = ceildiv(m, P.at(i));
    }
  }
  // Floyd-Warshall algorithm
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dist[i][j] = min(dist[i][j], max(dist[i][k], dist[k][j]));
      }
    }
  }
  long long ans = INF;
  for (int s = 0; s < N; s++) {
    long long now = 0;
    for (int t = 0; t < N; t++) {
      if (s == t) {
        continue;
      }
      now = max(now, dist[s][t]);
    }
    ans = min(ans, now);
  }
  cout << ans << endl;
  return 0;
}
