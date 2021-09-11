// https://atcoder.jp/contests/joi2011ho/tasks/joi2011ho1
// https://qiita.com/drken/items/56a6b68edef8fc605821

#include <iostream>
#include <vector>
using namespace std;

int main() {
  int M, N;
  cin >> M >> N;
  int K;
  cin >> K;
  vector<string> map(M);
  for (int m = 0; m < M; m++) {
    cin >> map.at(m);
  }
  vector<vector<int> > count_j(M + 1, vector<int>(N + 1, 0));
  vector<vector<int> > count_o(M + 1, vector<int>(N + 1, 0));
  vector<vector<int> > count_i(M + 1, vector<int>(N + 1, 0));
  for (int p = 1; p <= M; p++) {
    for (int q = 1; q <= N; q++) {
      if (map.at(p - 1).at(q - 1) == 'J') {
        count_j.at(p).at(q)++;
      } else if (map.at(p - 1).at(q - 1) == 'O') {
        count_o.at(p).at(q)++;
      } else {
        count_i.at(p).at(q)++;
      }
    }
  }
  vector<vector<int> > sum_j(M + 1, vector<int>(N + 1, 0));
  vector<vector<int> > sum_o(M + 1, vector<int>(N + 1, 0));
  vector<vector<int> > sum_i(M + 1, vector<int>(N + 1, 0));
  for (int p = 1; p <= M; p++) {
    for (int q = 1; q <= N; q++) {
      sum_j.at(p).at(q) = sum_j.at(p - 1).at(q) + sum_j.at(p).at(q - 1)
        - sum_j.at(p - 1).at(q - 1) + count_j.at(p).at(q);
      sum_o.at(p).at(q) = sum_o.at(p - 1).at(q) + sum_o.at(p).at(q - 1)
        - sum_o.at(p - 1).at(q - 1) + count_o.at(p).at(q);
      sum_i.at(p).at(q) = sum_i.at(p - 1).at(q) + sum_i.at(p).at(q - 1)
        - sum_i.at(p - 1).at(q - 1) + count_i.at(p).at(q);
    }
  }
  for (int k = 0; k < K; k++) {
    int top, left, bottom, right;
    cin >> top >> left >> bottom >> right;
    int j = sum_j.at(top - 1).at(left - 1) + sum_j.at(bottom).at(right)
      - sum_j.at(top - 1).at(right) - sum_j.at(bottom).at(left - 1);
    int o = sum_o.at(top - 1).at(left - 1) + sum_o.at(bottom).at(right)
      - sum_o.at(top - 1).at(right) - sum_o.at(bottom).at(left - 1);
    int i = sum_i.at(top - 1).at(left - 1) + sum_i.at(bottom).at(right)
      - sum_i.at(top - 1).at(right) - sum_i.at(bottom).at(left - 1);
    cout << j << ' ' << o << ' ' << i << endl;
  }
  return 0;
}
