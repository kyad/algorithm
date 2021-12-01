// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1167&lang=jp
// 複数選択できるナップサック問題

#include <iostream>
#include <vector>
using namespace std;

int main() {
  const int N = 1000000;
  vector<int> pollock, pollock_odd;
  for (int n = 1;; n++) {
    int a = n * (n + 1) * (n + 2) / 6;
    if (a > N) {
      break;
    }
    pollock.push_back(a);
    if (a % 2) {
      pollock_odd.push_back(a);
    }
  }
  int M0 = (int)pollock.size();
  vector<vector<int> > dp0(N + 1, vector<int>(2));
  // m = 0
  for (int n = 0; n <= N; n++) {
    dp0[n][0] = n;
  }
  for (int m = 1; m < M0; m++) {
    int M = pollock[m];
    dp0[0][m % 2] = 0;
    for (int n = 1; n <= N; n++) {
      dp0[n][m % 2] = dp0[n][1 - m % 2];
      if (n - M >= 0) {
        dp0[n][m % 2] = min(dp0[n][m % 2], dp0[n - M][1 - m % 2] + 1);
        dp0[n][m % 2] = min(dp0[n][m % 2], dp0[n - M][m % 2] + 1);
      }
    }
  }

  int M1 = (int)pollock_odd.size();
  vector<vector<int> > dp1(N + 1, vector<int>(2));
  // m = 0
  for (int n = 0; n <= N; n++) {
    dp1[n][0] = n;
  }
  for (int m = 1; m < M1; m++) {
    int M = pollock_odd[m];
    dp1[0][m % 2] = 0;
    for (int n = 1; n <= N; n++) {
      dp1[n][m % 2] = dp1[n][1 - m % 2];
      if (n - M >= 0) {
        dp1[n][m % 2] = min(dp1[n][m % 2], dp1[n - M][1 - m % 2] + 1);
        dp1[n][m % 2] = min(dp1[n][m % 2], dp1[n - M][m % 2] + 1);
      }
    }
  }

  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    cout << dp0[n][1 - M0 % 2] << " " << dp1[n][1 - M1 % 2] << endl;
  }
  return 0;
}
