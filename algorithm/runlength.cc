// https://atcoder.jp/contests/arc157/tasks/arc157_b

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template<class T> vector<pair<int, T> > runlength(vector<T> A) {
  vector<pair<int, T> > ans;
  if (A.empty()) {
    return ans;
  }
  T now = A.at(0);
  int count = 1;
  for (size_t n = 1; n < A.size(); n++) {
    if (now == A.at(n)) {
      count++;
    } else {
      ans.push_back(make_pair(count, now));
      count = 1;
      now = A.at(n);
    }
  }
  if (count > 0) {
    ans.push_back(make_pair(count, now));
  }
  return ans;
}

vector<pair<int, char> > runlength(string S) {
  vector<char> A(S.size());
  for (size_t i = 0; i < S.size(); i++) {
    A.at(i) = S.at(i);
  }
  return runlength(A);
}

int solve(int N, int K, string S) {
  int n_X = count(S.begin(), S.end(), 'X');
  if (n_X < K) {
    string T(S);
    for (int n = 0; n < N; n++) {
      T[n] = (S[n] == 'X' ? 'Y' : 'X');
    }
    return solve(N, N - K, T);
  }

  if (n_X == N) {
    if (K == 0) {
      return 0;
    } else {
      return K - 1;
    }
  }

  vector<pair<int, char> > run = runlength(S);
  int M = run.size();

  // init
  int ans = 0;
  for (int m = 0; m < M; m++) {
    int l = run[m].first;
    char c = run[m].second;
    if (c == 'Y') {
      ans += l - 1;
    }
  }
  // mid
  auto solve_mid = [&](vector<int> X) {
    for (int l : X) {
      if (K <= 0) {
        break;
      }
      int take = min(K, l);
      int score = take + (take == l ? 1 : 0);
      ans += score;
      K -= take;
    }
  };

  // X --> Y
  vector<int> Xedge;
  vector<int> Xmid;
  for (int m = 0; m < M; m++) {
    int l = run[m].first;
    char c = run[m].second;
    if (c != 'X') {
      continue;
    }
    bool edge = (m == 0 || m == M - 1);
    if (!edge) {
      Xmid.push_back(l);
    }
  }
  sort(Xmid.begin(), Xmid.end());
  solve_mid(Xmid);
  ans += K;
  return ans;
}

int main() {
  int N, K;
  cin >> N >> K;
  string S;
  cin >> S;
  int ans = solve(N, K, S);
  cout << ans << endl;
  return 0;
}
