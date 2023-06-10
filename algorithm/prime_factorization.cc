// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A&lang=ja

#include <iostream>
#include <vector>
using namespace std;

// O(sqrt(n))
vector<int> prime_factorization(int n) {
  vector<int> ans;
  for (long long m = 2; m * m <= ((long long)n); m++) {  // Care for overflow
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

int main() {
  int n;
  cin >> n;
  cout << n << ":";
  vector<int> ans = prime_factorization(n);
  for (size_t i = 0; i < ans.size(); i++) {
    cout << ' ' << ans.at(i);
  }
  cout << endl;
  return 0;
}
