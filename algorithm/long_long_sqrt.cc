// https://atcoder.jp/contests/abc280/tasks/abc280_d

#include <iostream>
#include <map>
#include <vector>
using namespace std;

// (long long)(sqrt(n)) for n >= 0
const long long INF = 1000001;  // Please set INF >= max(n) + 1.
long long long_long_sqrt(long long n) {
  if (n == 0) {
    return 0;
  }    
  long long left = 0;
  long long right = INF;
  while (right - left > 1) {
    long long mid = (left + right) / 2;
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
vector<long long> prime_factorization(long long n) {
  long long max = long_long_sqrt(n);
  //print(n, max);
  vector<long long> ans;
  for (long long m = 2; m <= max; m++) {
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

long long solve(long long p, int cnt) {
  long long n = p;
  while (true) {
    long long now = n;
    while (now % p == 0) {
      now /= p;
      cnt--;
      if (cnt == 0) {
        break;
      }
    }
    if (cnt == 0) {
      break;
    }
    n += p;
  }
  return n;
}

int main() {
  long long K;
  cin >> K;
  vector<long long> ps = prime_factorization(K);
  map<long long, int> mp;
  for (size_t i = 0; i < ps.size(); i++) {
    long long p = ps[i];
    mp[p]++;
  }
  long long ans = 0;
  for (auto [p, cnt] : mp) {
    long long now = solve(p, cnt);
    ans = max(ans, now);
  }
  cout << ans << endl;
  return 0;
}
