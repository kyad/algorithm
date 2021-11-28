// https://atcoder.jp/contests/joi2012ho/tasks/joi2012ho4
// https://imoz.jp/algorithms/imos_method.html

#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int> > imos(N + 2, vector<int>(N + 2, 0));
  for (int m = 0; m < M; m++) {
    int A, B, X;
    cin >> A >> B >> X;
    A--;
    B--;
    imos.at(A).at(B)++;
    imos.at(A).at(B + 1)--;
    imos.at(A + X + 1).at(B)--;
    imos.at(A + X + 2).at(B + 1)++;
    imos.at(A + X + 1).at(B + X + 2)++;
    imos.at(A + X + 2).at(B + X + 2)--;
  }
  for (int a = 0; a < N + 2; a++) {
    for (int b = 0; b < N + 1; b++) {
      imos.at(a).at(b + 1) += imos.at(a).at(b);
    }
  }
  for (int b = 0; b < N + 2; b++) {
    for (int a = 0; a < N + 1; a++) {
      imos.at(a + 1).at(b) += imos.at(a).at(b);
    }
  }
  for (int a = 0; a < N + 1; a++) {
    // a + c + 1 < N + 2 <=> c < N - a + 1
    for (int c = 0; c < N - a + 1; c++) {
      imos.at(a + c + 1).at(c + 1) += imos.at(a + c).at(c);
    }
  }
  int ans = 0;
  for (int a = 0; a < N; a++) {
    for (int b = 0; b <= a; b++) {
      if (imos.at(a).at(b) > 0) {
        ans++;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
