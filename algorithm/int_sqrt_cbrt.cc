// https://atcoder.jp/contests/arc113/tasks/arc113_a

#include <iostream>
using namespace std;

// int(sqrt(n)) for n >= 0
int int_sqrt(int n) {
  if (n == 0) {
    return 0;
  }    
  int left = 0;
  int right = 200001;
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

// int(cbrt(n)) for n >= 0
int int_cbrt(int n) {
  if (n == 0) {
    return 0;
  }    
  int left = 0;
  int right = 200001;
  while (right - left > 1) {
    int mid = (left + right) / 2;
    long long y = (long long)mid * mid * mid - n;
    if (y <= 0) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return left;
}

int main() {
  int K;
  cin >> K;
  int ans = 0;
  for (int A = 1; A <= int_cbrt(K); A++) {
    for (int B = A; B <= int_sqrt(K / A); B++) {
      if (A == B) {
        ans++;
        if (K / A / B - B > 0) {
          ans += (K / A / B - B) * 3;
        }
      } else {
        ans += 3;
        if (K / A / B - B > 0) {
          ans += (K / A / B - B) * 6;
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
