// https://atcoder.jp/contests/abc150/tasks/abc150_c

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> P(N);
  for (int n = 0; n < N; n++) {
    cin >> P.at(n);
  }
  vector<int> Q(N);
  for (int n = 0; n < N; n++) {
    cin >> Q.at(n);
  }
  vector<int> A(N);
  for (int n = 0; n < N; n++) {
    A.at(n) = n + 1;
  }
  int a, b;
  int count = 0;
  do {
    if (A == P) {
      a = count;
    }
    if (A == Q) {
      b = count;
    }
    count++;
  } while (next_permutation(A.begin(), A.end()));
  cout << abs(a - b) << endl;
  return 0;
}
