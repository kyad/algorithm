// https://atcoder.jp/contests/abc296/tasks/abc296_d

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template<class T> T ceildiv(T a, T b) {
  return (a + b - 1) / b;
}

// 引数としてlong longの値を取り、答がintの範囲で収まる場合に動作するint_sqrt
// int(sqrt(n)) for 0 <= n <= 10^18
// 計算量 O(log(RIGHT_MAX))
int int_sqrt(long long n) {
  if (n == 0) {
    return 0;
  }    
  int left = 0;
  const int RIGHT_MAX = 1e9+1;  // >= sqrt(max(n)). 2乗してlong longの範囲に収まること
  int right = RIGHT_MAX;
  while (right - left > 1) {
    int mid = (left + right) / 2;
    long long y = (long long)mid * mid - n;
    if (y <= 0) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return left;
}

int main() {
  long long N, M;
  cin >> N >> M;
  const long long INF = 4e18;
  long long ans = INF;
  for (long long a = 1; a <= int_sqrt(M) + 1; a++) {
    long long b = ceildiv(M, a);
    if (a > N || b > N) {
      continue;
    }
    long long X = b * a;
    if (X >= M) {
      ans = min(ans, X);
    }
  }
  if (ans == INF) {
    ans = -1;
  }
  cout << ans << endl;
  return 0;
}
