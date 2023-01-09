#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// sqrt(n) for long long. To avlid overflow of middle * middle, We use sqrt.
#include <cmath>
long long long_long_sqrt(long long n) { return round(sqrt(n)); }

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

// Sieve of Eratosthenes  O(N * log log (N))
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
  int M = 3000000;
  vector<bool> is_prime = eratosthenes(M);
  vector<long long> primes;
  for (int m = 2; m <= M; m++) {
    if (is_prime[m]) {
      primes.push_back(m);
    }
  }
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    // testcase
    long long N;
    cin >> N;
    bool ok = false;
    // Fix p
    for (long long p : primes) {
      if (p * p > N) {
        break;
      }
      long long q = N / p / p;
      if (p * p * q != N) {
        continue;
      }
      cout << p << ' ' << q << '\n';
      ok = true;
      break;
    }
    if (ok) {
      continue;
    }
    // Fix q
    for (long long q : primes) {
      long long p2 = N / q;
      long long p = long_long_sqrt(p2);
      if (p * p * q != N) {
        continue;
      }
      cout << p << ' ' << q << '\n';
      ok = true;
      break;
    }
    if (ok) {
      continue;
    }
    assert(false);
  }
  return 0;
}
