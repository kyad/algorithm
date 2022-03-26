// https://atcoder.jp/contests/abc244/tasks/abc244_c

#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  int M = 2 * N + 1;
  vector<bool> used(M + 1, false);
  while (true) {
    // Takahashi
    int t = 1;
    for (t = 1; t <= M; t++) {
      if (!used[t]) {
        used[t] = true;
        break;
      }
    }
    cout << t << endl;
    cout << flush;
    // Aoki
    int a;
    cin >> a;
    if (a == 0) {
      return 0;
    }
    used[a] = true;
  }
  return 0;
}
