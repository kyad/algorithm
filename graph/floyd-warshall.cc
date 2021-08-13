// https://atcoder.jp/contests/abc143/tasks/abc143_e
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_5.cpp

#include <iostream>
#include <vector>
using namespace std;

int main() {
  const long long INF = 1000000000LL * 300 + 1;
  int N, M, L;
  cin >> N >> M >> L;
  vector<vector<long long> > dp(N, vector<long long>(N, INF));
  for (int n = 0; n < N; n++) {
    dp[n][n] = 0;
  }
  for (int m = 0; m < M; m++) {
    int A, B, C;
    cin >> A >> B >> C;
    dp[A - 1][B - 1] = C;
    dp[B - 1][A - 1] = C;
  }
  // Floyd-Warshall algorithm
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
      }
    }
  }
  bool exist_negative_cycle = false;
  for (int n = 0; n < N; n++) {
    if (dp[n][n] < 0) {
      exist_negative_cycle = true;
    }
  }

  vector<vector<long long> > dp2(N, vector<long long>(N, INF));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) {
        dp2[i][j] = 0;
      } else if (dp[i][j] <= L) {
        dp2[i][j] = 1;
      }
    }
  }
  // Floyd-Warshall algorithm
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dp2[i][j] = min(dp2[i][j], dp2[i][k] + dp2[k][j]);
      }
    }
  }

  int Q;
  cin >> Q;
  for (int q = 0; q < Q; q++) {
    int s, t;
    cin >> s >> t;
    cout << (dp2[s - 1][t - 1] == INF ? -1 : (dp2[s - 1][t - 1] - 1)) << endl;
  }
  return 0;
}
