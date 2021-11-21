// https://atcoder.jp/contests/abc228/tasks/abc228_d

#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
  const int N = 1048576;
  vector<long long> A(N, -1);
  map<int, int> interval;  // interval[end] = begin, [begin, end)
  interval[N] = 0;
  int Q;
  cin >> Q;
  for (int q = 0; q < Q; q++) {
    int t;
    long long x;
    cin >> t >> x;
    if (t == 1) {
      int h = x % N;
      map<int, int>::iterator it = interval.upper_bound(h);
      if (it == interval.end()) {
        it = interval.begin();
        h = -1;
      }
      int begin = it->second;
      int end = it->first;
      if (begin <= h) {  // A[h] = -1
        A[h] = x;
        interval.erase(end);
        if (h > begin) {
          interval[h] = begin;
        }
        if (h + 1 < end) {
          interval[end] = h + 1;
        }
      } else {  // A[h] != -1
        A[begin] = x;
        interval.erase(end);
        if (begin + 1 < end) {
          interval[end] = begin + 1;
        }
      }
    } else {  // t == 2
      cout << A[x % N] << endl;
    }
  }
  return 0;
}
