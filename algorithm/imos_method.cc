// https://atcoder.jp/contests/abc014/tasks/abc014_3
// https://imoz.jp/algorithms/imos_method.html

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Imos method
int main() {
  int n;
  cin >> n;
  vector<int> diff(1000002, 0);
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    diff[a]++;
    diff[b + 1]--;
  }
  for (size_t i = 1; i < diff.size(); i++) {
    diff[i] += diff[i - 1];
  }
  cout << *max_element(diff.begin(), diff.end() - 1) << endl;
  return 0;
}
