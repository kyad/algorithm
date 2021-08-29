// https://atcoder.jp/contests/abc216/tasks/abc216_d
// https://atcoder.jp/contests/apg4b/tasks/APG4b_aa

#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<queue<int> > a;
  for (int m = 0; m < M; m++) {
    int k;
    cin >> k;
    queue<int> aa;
    for (int i = 0; i < k; i++) {
      int aaa;
      cin >> aaa;
      aa.push(aaa);
    }
    a.push_back(aa);
  }
  map<int, int> top_map;
  queue<int> q;
  for (int i = 0; i < M; i++) {
    q.push(i);
  }
  while (!q.empty()) {
    int m = q.front();
    q.pop();
    if (a[m].empty()) {
      continue;
    }
    int top_value = a[m].front();
    a[m].pop();
    if (top_map.count(top_value) > 0) {
      int value = top_map[top_value];
      q.push(value);
      q.push(m);
      top_map.erase(top_value);
    } else {
      top_map[top_value] = m;
    }
  }
  string ans = "Yes";
  for (int m = 0; m < M; m++) {
    if (!a[m].empty()) {
      ans = "No";
      break;
    }
  }
  cout << ans << endl;
  return 0;
}
