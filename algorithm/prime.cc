// https://atcoder.jp/contests/abc239/tasks/abc239_d

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

vector<int> prime_factorization(int n) {
  int max = (int)sqrt(n);
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
