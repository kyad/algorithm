// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A&lang=ja

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
