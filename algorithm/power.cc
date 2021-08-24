// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B&lang=ja
// https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a

#include <iostream>
using namespace std;

// m^n, O(log n)
int power(int m, int n, int mod) {
  long long a = m;
  long long ans = 1;
  while (n > 0) {
    if (n & 1 == 1) {
      ans *= a;
      ans %= mod;
    }
    a *= a;
    a %= mod;
    n >>= 1;
  }
  return ans;
}

int main() {
  int m, n;
  cin >> m >> n;
  cout << power(m, n, 1000000007) << endl;
  return 0;
}
