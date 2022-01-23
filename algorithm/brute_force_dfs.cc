// https://atcoder.jp/contests/abc236/tasks/abc236_d

#include <iostream>
#include <vector>
using namespace std;

int N;
vector<vector<int> > A;
vector<bool> used;

int dfs(int depth, int u, int value) {
  int v = 0;
  for (v = 0; v < 2 * N; v++) {
    if (!used[v]) {
      break;
    }
  }

  if (depth == N - 1) {
    value ^= A[u][v];
    return value;
  }

  used[v] = true;
  int ans = 0;
  for (int w = 0; w < 2 * N; w++) {
    if (used[w]) {
      continue;
    }
    used[w] = true;
    ans = max(ans, dfs(depth + 1, w, value ^ A[u][v]));
    used[w] = false;
  }
  used[v] = false;
  return ans;
}

int main() {
  cin >> N;
  A.resize(2 * N, vector<int>(2 * N, 0));
  for (int i = 0; i < 2 * N; i++) {
    for (int j = i + 1; j < 2 * N; j++) {
      cin >> A[i][j];
    }
  }
  for (int i = 0; i < 2 * N; i++) {
    for (int j = 0; j < i; j++) {
      A[i][j] = A[j][i];
    }
  }
  used.resize(2 * N, false);
  int ans = 0;
  // Brute-force search by DFS
  // Select N values from {0, 1, 2, ...., 2 * N - 1}
  for (int u = 0; u < 2 * N; u++) {
    used[u] = true;
    ans = max(ans, dfs(0, u, 0));
    used[u] = false;
  }
  cout << ans << endl;
  return 0;
}
