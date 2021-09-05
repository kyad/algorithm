// https://atcoder.jp/contests/abc217/tasks/abc217_e

#include <iostream>
#include <queue>
#include <set>
using namespace std;

int main() {
  int Q;
  cin >> Q;
  queue<int> q;
  multiset<int> ms;
  for (int i = 0; i < Q; i++) {
    int query, x;
    cin >> query;
    if (query == 1) {
      cin >> x;
      q.push(x);
    } else if (query == 2) {
      if (!ms.empty()) {
        cout << *ms.begin() << endl;
        ms.erase(ms.begin());
      } else {
        cout << q.front() << endl;
        q.pop();
      }
    } else {
      while (!q.empty()) {
        ms.insert(q.front());
        q.pop();
      }
    }
  }
  return 0;
}
