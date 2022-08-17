// https://atcoder.jp/contests/abc263/tasks/abc263_c
// https://kopricky.github.io/code/Computation_Basic/next_combination.html

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

static void show(vector<int> ans) {
  for (size_t i = 0; i < ans.size(); i++) {
    cout << (ans.at(i) + 1) << ' ';
  }
  cout << endl;
}

int main() {
  int N, M;
  cin >> N >> M;

  // Next combination. Select N from M
  vector<bool> mask(M, true);
  fill(mask.begin(), mask.begin() + N, false);
  do {
    vector<int> ans;
    for (int i = 0; i < M; i++) {
      if (!mask[i]) {
        ans.push_back(i);
      }
    }
    show(ans);
  } while (next_permutation(mask.begin(), mask.end()));
  return 0;
}
