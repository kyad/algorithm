// https://atcoder.jp/contests/abc228/tasks/abc228_f

#include <cassert>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Sliding Window Aggregation (SWAG)
// スタック内の最大値を保存するスタック。全てO(1)
template<class T> struct MaxStack {
  stack<T> a, mx;
  T get_max() { return mx.size() ? mx.top() : 0; }
  void push(T x) {
    a.push(x);
    mx.push(max(x, get_max()));
  }
  T top() { assert(a.size()); return a.top(); }
  void pop() { a.pop(); mx.pop(); }
  size_t size() { return a.size(); }
};

// キュー内の最大値を保存するキュー
template<class T> struct MaxQueue {
  MaxStack<T> s, t;
  void mv() {
    while (t.size()) {
      s.push(t.top());
      t.pop();
    }
  }
  void push(T x) { t.push(x); }  // O(1)
  void pop() {  // ならしO(1)
    if (!s.size()) mv();
    s.pop();
  }
  T get_max() {  // O(1)
    return max(s.get_max(), t.get_max());
  }
};

template<class T> ostream& operator<<(ostream& os, const stack<T> &s) {
  stack<T> _s(s);
  vector<T> v;
  while (!_s.empty()) {
    v.push_back(_s.top());
    _s.pop();
  }
  os << '[';
  for (int i = v.size() - 1; i >= 0; i--) {
    os << v[i];
    if (i != 0) {
      os << ' ';
    }
  }
  os << ']';
  return os;
}

template<class T> ostream& operator<<(ostream& os, const MaxStack<T> &ms) {
  os << "val=" << ms.a << endl;
  os << "max=" << ms.mx << endl;
  return os;
}

template<class T> ostream& operator<<(ostream& os, const MaxQueue<T> &mq) {
  os << "val=" << mq.s.a << mq.t.a << endl;
  os << "max=" << mq.s.mx << mq.t.mx << endl;
  return os;
}

int main() {
  int H, W, h1, w1, h2, w2;
  cin >> H >> W >> h1 >> w1 >> h2 >> w2;
  h2 = min(h2, h1);
  w2 = min(w2, w1);
  vector<vector<long long> > A(H + 1, vector<long long>(W + 1, 0));  // 1-indexed
  for (int y = 1; y <= H; y++) {
    for (int x = 1; x <= W; x++) {
      cin >> A.at(y).at(x);
    }
  }
  for (int y = 1; y <= H; y++) {
    for (int x = 1; x <= W; x++) {
      A[y][x] += A[y][x - 1];
    }
  }
  for (int x = 1; x <= W; x++) {
    for (int y = 1; y <= H; y++) {
      A[y][x] += A[y - 1][x];
    }
  }
  // Taka[y][x]: (x, y)から(x+w1, y+h1)までの和 (1-indexed)
  vector<vector<long long> > Taka(H - h1 + 1 + 1, vector<long long>(W - w1 + 1 + 1, 0));
  for (int y = 1; y <= H - h1 + 1; y++) {
    for (int x = 1; x <= W - w1 + 1; x++) {
      Taka[y][x] = A[y + h1 - 1][x + w1 - 1] - A[y + h1 - 1][x - 1] - A[y - 1][x + w1 - 1] + A[y - 1][x - 1];
    }
  }
  // Aoki[y][x]: (x, y)から(x+w2, y+h2)までの和 (1-indexed)
  vector<vector<long long> > Aoki(H - h2 + 1 + 1, vector<long long>(W - w2 + 1 + 1, 0));
  for (int y = 1; y <= H - h2 + 1; y++) {
    for (int x = 1; x <= W - w2 + 1; x++) {
      Aoki[y][x] = A[y + h2 - 1][x + w2 - 1] - A[y + h2 - 1][x - 1] - A[y - 1][x + w2 - 1] + A[y - 1][x - 1];
    }
  }
  // P: Aoki[y][x]のx方向の幅w1-w2+1のスライド最小値
  vector<vector<long long> > P(H - h2 + 1 + 1, vector<long long>(W - w1 + 1 + 1, 0));
  for (int y = 1; y <= H - h2 + 1; y++) {
    MaxQueue<long long> q;
    for (int i = 0; i < w1 - w2; i++) {
      q.push(Aoki[y][i + 1]);
    }
    for (int x = 1; x <= W - w1 + 1; x++) {
      q.push(Aoki[y][w1 - w2 + x]);
      P[y][x] = q.get_max();
      q.pop();
    }
  }
  // Q: Aoki[y][x]のx方向の幅w1-w2+1、y方向の幅h1-h2+1のスライド最小値
  vector<vector<long long> > Q(H - h1 + 1 + 1, vector<long long>(W - w1 + 1 + 1, 0));
  for (int x = 1; x <= W - w1 + 1; x++) {
    MaxQueue<long long> q;
    for (int i = 0; i < h1 - h2; i++) {
      q.push(P[i + 1][x]);
    }
    for (int y = 1; y <= H - h1 + 1; y++) {
      q.push(P[h1 - h2 + y][x]);
      Q[y][x] = q.get_max();
      q.pop();
    }
  }
  long long ans = 0;
  for (int y = 1; y <= H - h1 + 1; y++) {
    for (int x = 1; x <= W - w1 + 1; x++) {
      ans = max(ans, Taka[y][x] - Q[y][x]);
    }
  }
  cout << ans << endl;
  return 0;
}
