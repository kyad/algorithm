// https://atcoder.jp/contests/abc213/tasks/abc213_c

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Return 0-order compressed vector whose size is same as A
vector<int> compress(vector<int> A) {
  vector<int> a(A);
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  map<int, int> m;
  for (size_t i = 0; i < a.size(); i++) {
    m[a[i]] = i;
  }
  vector<int> ans(A.size());
  for (size_t i = 0; i < A.size(); i++) {
    ans[i] = m[A[i]];
  }
  return ans;
}

int main() {
  int H, W, N;
  cin >> H >> W >> N;
  vector<int> A(N);
  vector<int> B(N);
  for (int n = 0; n < N; n++) {
    cin >> A.at(n) >> B.at(n);
  }
  vector<int> C = compress(A);
  vector<int> D = compress(B);
  for (int n = 0; n < N; n++) {
    cout << (C.at(n) + 1) << ' ' << (D.at(n) + 1) << endl;
  }
  return 0;
}
