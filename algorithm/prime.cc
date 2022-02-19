// https://atcoder.jp/contests/abc239/tasks/abc239_d

#include <iostream>
#include <vector>
using namespace std;

// int(sqrt(n)) for n >= 0
const int INF = 100000;
int int_sqrt(int n) {
  if (n == 0) {
    return 0;
  }    
  int left = 0;
  int right = INF;
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

// O(sqrt(n))
vector<int> prime_factorization(int n) {
  int max = int_sqrt(n);
  vector<int> ans;
  for (int m = 2; m <= max; m++) {
    while (n % m == 0) {
      n /= m;
      ans.push_back(m);
    }
  }
  if (n != 1) {
    ans.push_back(n);
  }
  return ans;
}

// O(sqrt(n))
bool is_prime(int n) {
  vector<int> v = prime_factorization(n);
  return (v.size() == 1);
}

int main() {
  int A, B, C, D;
  cin >> A >> B >> C >> D;
  string ans = "Aoki";
  for (int t = A; t <= B; t++) { // 100
    bool ok = true;
    for (int a = C; a <= D; a++) { // 100
      int temp = t + a;
      if (is_prime(temp)) {
        ok = false;
      }
    }
    if (ok) {
      ans = "Takahashi";
    }
  }
  cout << ans << endl;
  return 0;
}
