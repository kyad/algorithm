// https://atcoder.jp/contests/abc084/tasks/abc084_d

#include <iostream>
#include <vector>
using namespace std;

// int(sqrt(N))  O(log(N))
int int_sqrt(int N) {
  int left = 0;
  int right = N;
  while (right - left > 1) {
    int middle = (left + right) / 2;
    if (middle * middle >= N) {
      right = middle;
    } else {
      left = middle;
    }
  }
  if (right * right >= N) {
    return right;
  } else {
    return left;
  }
}

// Sieve of Eratosthenes  O(N * sqrt(N))
vector<bool> eratosthenes(int N) {
  vector<bool> is_prime(N + 1, true);
  is_prime.at(0) = false;
  if (N > 0) {
    is_prime.at(1) = false;
  }
  for (int k = 2; k < int_sqrt(N); k++) {
    for (int i = 2 * k; i <= N; i+=k) {
      is_prime.at(i) = false;
    }
  }
  return is_prime;
}

int main() {
  vector<bool> is_prime = eratosthenes(100001);
  vector<bool> is_2017_like(100001, false);
  for (int n = 1; n < 100001; n+=2) {
    if (is_prime.at(n) && is_prime.at((n + 1) / 2)) {
      is_2017_like.at(n) = true;
    }
  }
  vector<int> sum(100001);
  sum.at(0) = 0;
  for (int n = 1; n < 100001; n++) {
    if (is_2017_like.at(n)) {
      sum.at(n) = sum.at(n - 1) + 1;
    } else {
      sum.at(n) = sum.at(n - 1);
    }
  }
  int Q;
  cin >> Q;
  for (int q = 0; q < Q; q++) {
    int l, r;
    cin >> l >> r;
    cout << (sum.at(r) - sum.at(l - 1)) << endl;
  }
  return 0;
}
