// https://atcoder.jp/contests/tenka1-2018-beginner/tasks/tenka1_2018_d
// https://kopricky.github.io/code/Computation_Basic/next_combination.html

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  const int n_max = 100000;
  vector<int> n_to_k(n_max + 1, -1);
  for (int k = 2;; k++) {
    int value = k * (k - 1) / 2;
    if (value > n_max) {
      break;
    }
    n_to_k[value] = k;
  }
  int N;
  cin >> N;
  int k = n_to_k[N];
  if (k < 0) {
    cout << "No" << endl;
    return 0;
  }
  cout << "Yes" << endl;
  cout << k << endl;

  vector<vector<int> > ans(k);
  int n = 1;

  // next_combination
  vector<bool> mask(k, false);
  fill(mask.end() - 2, mask.end(), true);
  do {
    for (int i = 0; i < k; i++) {
      if (mask[i]) {
        ans[i].push_back(n);
      }
    }
    n++;
  } while (next_permutation(mask.begin(), mask.end()));

  for (int i = 0; i < k; i++) {
    cout << ans[i].size();
    for (size_t j = 0; j < ans[i].size(); j++) {
      cout << ' ' << ans[i][j];
    }
    cout << endl;
  }
  return 0;
}
