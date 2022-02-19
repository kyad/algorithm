// https://atcoder.jp/contests/abc239/tasks/abc239_b

#include <iostream>
using namespace std;

long long ceil(long long a, long long b) {
  return (a + b - 1) / b;
}

int main() {
  long long X;
  cin >> X;
  long long ans;
  if (X > 0) {
    ans = X / 10;
  } else if (X < 0) {
    ans = -ceil(-X, 10);
  } else {
    ans = 0;
  }
  cout << ans << endl;
  return 0;
}
