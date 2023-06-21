// https://atcoder.jp/contests/abc303/tasks/abc303_f

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using l3 = __int128;

template<class T> void chmax(T& a, const T b) { a = max(a, b); }

template<class T> T ceildiv(T a, T b) {
  return (a + b - 1) / b;
}

int main() {
  int N;
  long long _H;
  cin >> N >> _H;
  l3 H = _H;
  map<int, int> e;  // t -> max d_t
  for (int n = 0; n < N; n++) {
    int t, d;
    cin >> t >> d;
    if (e.count(t) > 0) {
      chmax(e[t], d);
    } else {
      e[t] = d;
    }
  }
  // Remove t and d such that t * d does not increase
  {
    const long long INF = 4e18;
    long long mx = -INF;
    vector<int> removes;
    for (map<int, int>::iterator it = e.begin(); it != e.end(); it++) {
      long long t = it->first;
      long long d = it->second;
      long long td = t * d;
      if (td > mx) {
        mx = td;
      } else {
        removes.push_back(t);
      }
    }
    for (int t : removes) {
      e.erase(t);
    }
  }
  // e_t --> f_t = max_t'>=t e_t'
  {
    const int INF = 1e9;
    int mx = -INF;
    vector<int> removes;
    for (map<int, int>::reverse_iterator it = e.rbegin(); it != e.rend(); it++) {
      if (it->second > mx) {
        mx = it->second;
      } else {
        removes.push_back(it->first);
      }
    }
    for (int t : removes) {
      e.erase(t);
    }
  }

  vector<int> us;
  vector<int> fs;
  for (map<int, int>::iterator it = e.begin(); it != e.end(); it++) {
    us.push_back(it->first);
    fs.push_back(it->second);
  }

  int K = us.size();
  long long M = 0;
  long long t = 0;
  for (int k = 0; k < K; k++) {
    long long u = us[k];  // int
    long long f = fs[k];  // int
    long long s = M / f;
    {
      // sim <= s
      l3 D = (s - t) * M;
      if (H <= D) {
        // sim
        l3 ans = ceildiv(H, (l3)M) + t;
        cout << (long long)ans << endl;
        return 0;
      }
      H -= D;
      t = s;
    }
    {
      // sim <= u
      // 時刻tからxまでのダメージの合計
      auto damages = [&](l3 x) -> l3 {
        l3 D = 1;
        D *= (x + t + 1);
        D *= (x - t);
        D /= 2;
        D *= f;
        return D;
      };
      l3 D = damages(u);
      if (H <= D) {
        // sim
        l3 left = t; // NG
        l3 right = u; // OK
        while (right - left > 1) {
          l3 mid = (left + right) / 2;
          if (H - damages(mid) <= 0) {
            right = mid;
          } else {
            left = mid;
          }
        }
        cout << (long long)right << endl;
        return 0;
      }
      H -= D;
      t = u;
      M = u * f;
    }
  }
  // same as sim <= s
  l3 ans = ceildiv(H, (l3)M) + t;
  cout << (long long)ans << endl;
  return 0;
}
