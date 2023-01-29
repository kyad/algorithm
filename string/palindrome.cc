// https://atcoder.jp/contests/arc155/tasks/arc155_a

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// 回文かどうか判定する。計算量はO(|S|)
bool is_palindrome(const string &S) {
  int N = S.size();
  bool ans = true;
  for (int i = 0; i < N / 2; i++) {
    if (S[i] != S[N - 1 - i]) {
      ans = false;
      break;
    }
  }
  return ans;
}

bool solve(const string &S, long long N, long long K) {
  K %= (N * 4);
  if (K <= N) {
    if (S.substr(0, K) != S.substr(N - K, K)) {
      return false;
    }
    string T = S.substr(0, N - K);
    if (!is_palindrome(T)) {
      return false;
    }
    string U = S.substr(K, N - K);
    if (!is_palindrome(U)) {
      return false;
    }
    return true;
  }
  if (K <= 2 * N) {
    long long l = 2 * N - K;
    string R(S);
    reverse(R.begin(), R.end());
    if (R.substr(0, l) != R.substr(K - N, l)) {
      return false;
    }
    if (!is_palindrome(R.substr(0, K - N))) {
      return false;
    }
    if (!is_palindrome(R.substr(l, K - N))) {
      return false;
    }
    return true;
  }
  // K > 2 * N;
  long long K2 = K - 2 * N;
  string S2(S);
  reverse(S2.begin(), S2.end());
  assert(K2 <= 2 * N);
  return solve(S2, N, K2);
}

void testcase() {
  int N;
  long long K;
  cin >> N >> K;
  string S;
  cin >> S;
  bool ans = solve(S, N, K);
  cout << (ans ? "Yes" : "No") << '\n';
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    testcase();
  }
  return 0;
}
