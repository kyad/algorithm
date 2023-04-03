// https://atcoder.jp/contests/abc293/tasks/abc293_f

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// m^n, O(log n)
long long power(long long m, long long n) {
  long long a = m;
  long long ans = 1;
  while (n > 0) {
    if ((n & 1) == 1) {
      ans *= a;
    }
    a *= a;
    n >>= 1;
  }
  return ans;
}

// int(nth_root of x) for x >= 0
long long int_nth_root(long long x, long long n) {
  long long left = 0;  // OK
  long long right = (long long)(pow(x, 1. / n) + 1.5);  // NG
  while (right - left >= 2) {
    long long mid = (left + right) / 2;
    if (power(mid, n) <= x) {  // これがオーバーフローしないこと。
      left = mid;
    } else {
      right = mid;
    }
  }
  return left;
}

int solve(long long N, int d) {
  if (d == 1) {
    // N(N)
    return 0;
  } else if (d == 2) {
    // 10(N-1), 11(N-1)
    if (N == 2) {
      return 1;
    } else {
      return 2;
    }
  }
  long long b = int_nth_root(N, d - 1);
  if (b <= 1) {
    return -1;  // end
  }
  long long x = N;
  int count = 0;
  while (x > 0) {
    long long r = x % b;
    if (r > 1) {
      return 0;  // NG
    }
    x /= b;
    count++;
  }
  if (count != d) {
    return 0;
  }
  return 1;
}

void testcase() {
  long long N;
  cin >> N;
  int ans = 0;
  for (int d = 1; d <= 64; d++) {
    int now = solve(N, d);
    if (now < 0) {
      break;
    }
    ans += now;
  }
  cout << ans << '\n';
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    testcase();
  }
  return 0;
}
