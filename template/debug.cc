#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
using namespace std;

// debug print
#define print1(a) std::cout << #a << '=' << a << std::endl;
#define print2(a, b) print1(a); print1(b);
#define print3(a, b, c) print1(a); print2(b, c);
#define print4(a, b, c, d) print1(a); print3(b, c, d);
#define print5(a, b, c, d, e) print1(a); print4(b, c, d, e);
#define print6(a, b, c, d, e, f) print1(a); print5(b, c, d, e, f);
#define print7(a, b, c, d, e, f, g) print1(a); print6(b, c, d, e, f, g);
#define print8(a, b, c, d, e, f, g, h) print1(a); print7(b, c, d, e, f, g, h);
#define print_select(a, b, c, d, e, f, g, h, i, ...) i
#define print(...) print_select(__VA_ARGS__, print8, print7, print6, print5, print4, print3, print2, print1)(__VA_ARGS__)

// pair
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1, T2> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

// vector
template<class T> ostream& operator<<(ostream& os, const vector<T> &v) {
  size_t N = v.size();
  int MOD = -1;
  os << '[';
  for (size_t i = 0; i < N; i++) {
    os << v[i];
    if (i == N - 1) {
      continue;
    } else if (MOD > 0 && i % MOD == (MOD - 1)) {
      os << '\n';
    } else {
      os << ' ';
    }
  }
  os << ']';
  return os;
}

// set
template<class T> ostream& operator<<(ostream& os, const set<T> &s) {
  os << '[';
  if (!s.empty()) {
    typename set<T>::iterator last = s.end();
    last--;
    for (typename set<T>::iterator it = s.begin(); it != s.end(); it++) {
      os << *it;
      if (it != last) {
        os << ' ';
      }
    }
  }
  os << ']';
  return os;
}

// multiset
template<class T> ostream& operator<<(ostream& os, const multiset<T> &ms) {
  os << '[';
  for (typename multiset<T>::iterator it = ms.begin(); it != ms.end(); it++) {
    os << *it;
    if (it != prev(ms.end())) {
      os << ' ';
    }
  }
  os << ']';
  return os;
}

// map
template<class T1, class T2> ostream& operator<<(ostream& os, const map<T1, T2> &m) {
  os << '[';
  size_t i = m.size();
  for (typename map<T1, T2>::const_iterator it = m.begin(); it != m.end(); it++) {
    os << '(' << it->first << " , " << it->second << ')';
    if (i > 1) {
      os << ' ';
    }
    i--;
  }
  os << ']';
  return os;
}

// queue
template<class T> ostream& operator<<(ostream& os, const queue<T> &q) {
  os << '[';
  queue<T> _q(q);
  while (!_q.empty()) {
    os << _q.front();
    _q.pop();
    if (!_q.empty()) {
      os << ' ';
    }
  }
  os << ']';
  return os;
}

// priority_queue
template<class T> ostream& operator<<(ostream& os, const priority_queue<T> &q) {
  os << '[';
  priority_queue<T> _q(q);
  while (!_q.empty()) {
    os << _q.top();
    _q.pop();
    if (!_q.empty()) {
      os << ' ';
    }
  }
  os << ']';
  return os;
}

// priority_queue (greater)
template<class T> ostream& operator<<(ostream& os, const priority_queue<T, vector<T>, greater<T> > &q) {
  os << '[';
  priority_queue<T, vector<T>, greater<T> > _q(q);
  while (!_q.empty()) {
    os << _q.top();
    _q.pop();
    if (!_q.empty()) {
      os << ' ';
    }
  }
  os << ']';
  return os;
}

// deque
template<class T> ostream& operator<<(ostream& os, const deque<T> &dq) {
  os << '[';
  for (auto it = dq.begin(); it != dq.end(); it++) {
    os << *it;
    if (it != prev(dq.end())) {
      os << ' ';
    }
  }
  os << ']';
  return os;
}

// stack
#include <vector>
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

// tuple3
template<class T1, class T2, class T3> ostream& operator<<(ostream& os, const tuple<T1, T2, T3> &t) {
  os << "(" << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ")";
  return os;
}

// bit
#include <bitset>
#define BIT (8)
string bitstr(int b) {
  return bitset<BIT>(b).to_string();
}

void print_bit(int b) {
  // Header
  for (int i = BIT - 1; i >= 0; i--) {
    cout << i;
  }
  cout << endl;
  // Main
  cout << bitstr(b) << endl;
}

// 1d-array (C)
template<class T> void print_vec(int N, T a[]) {
  vector<T> v(N);
  for (int n = 0; n < N; n++) {
    v[n] = a[n];
  }
  cout << v <<endl;
}

// 2d-matrix
template<class T> ostream& operator<<(ostream& os, const vector<vector<T> > &v) {
  int y0 = 0;
  int y1 = (int)v.size() - 1;
  for (int i = y0; i <= y1; i++) {
    os << (i == 0 ? "[[" : " [");
    int x0 = 0;
    int x1 = (int)v[i].size() - 1;
    for (int j = x0; j <= x1; j++) {
      os << v[i][j];
      if (j != x1) {
        os << ' ';
      }
    }
    os << (i == y1 ? "]]" : "]\n");
  }
  return os;
}

// 2d-matrix for bit DP
#include <bitset>
#define BIT (8)
template<class T> void print_bit_dp(const vector<vector<T> > &v) {
  const long long INF = 1000000000000 * 16 + 1;
  // Header
  for (int i = BIT - 1; i >= 0; i--) {
    cout << i;
  }
  cout << ' ';
  for (size_t j = 0; j < v[0].size(); j++) {
    cout << ' ' << j;
  }
  cout << endl;
  // Main
  for (size_t i = 0; i < v.size(); i++) {
    cout << bitset<BIT>(i) << " [";
    for (size_t j = 0; j < v[i].size(); j++) {
      if (v[i][j] >= INF) {
        cout << '_';
      } else {
        cout << v[i][j];
      }
      cout << (j == v[i].size() - 1 ? "]\n" : " ");
    }
  }
}

// 2d-matrix (C)
#include <iomanip>
template<class T> void print_mat(int h, int w, T a[][2000]) {
  const int fmtw = 4;
  for (int j = 0; j < fmtw + 1; j++) {
    cout << ' ';
  }
  for (int j = 0; j < w; j++) {
    cout << ' ' << right << setw(fmtw) << j;
  }
  cout << endl;
  for (int i = 0; i < h; i++) {
    cout << right << setw(fmtw) << i << " [";
    for (int j = 0; j < w; j++) {
      cout << right << setw(fmtw) << a[i][j] << (j == w - 1 ? "]\n" : " ");
    }
  }
}

// 3d-array for DP
template<class T> ostream& operator<<(ostream& os, const vector<vector<vector<T> > > &v) {
  size_t i0 = 0;
  size_t i1 = v.size() - 1;
  size_t j0 = 0;
  size_t j1 = v[0].size() - 1;
  for (size_t i = i0; i <= i1; i++) {
    for (size_t j = j0; j <= j1; j++) {
      os << i << ' ' << j << ':';
      size_t k0 = 0;
      size_t k1 = v[i][j].size() - 1;
      for (size_t k = k0; k <= k1; k++) {
        os << ' ' << v[i][j][k];
      }
      os << endl;
    }
  }
  return os;
}

int cmat[10][2000];
int main() {
  cout << make_pair(1, 2) << endl;
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  cout << "v=" << v << endl;
  set<int> s;
  s.insert(1);
  s.insert(2);
  cout << "s=" << s << endl;
  multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  cout << "ms=" << ms << endl;
  map<int, int> mp;
  mp[1] = 2;
  mp[3] = 10;
  mp[7] = 20;
  cout << "mp=" << mp << endl;
  queue<int> q;
  q.push(1);
  q.push(2);
  cout << "q=" << q << endl;
  priority_queue<int> pq;
  pq.push(2);
  pq.push(1);
  pq.push(5);
  cout << "pq=" << pq << endl;
  priority_queue<int, vector<int>, greater<int> > pqg;
  pqg.push(2);
  pqg.push(1);
  pqg.push(5);
  cout << "pqg=" << pqg << endl;
  deque<int> dq;
  dq.push_front(1);
  dq.push_back(2);
  cout << "dq=" << dq << endl;
  stack<int> st;
  st.push(1);
  st.push(2);
  cout << "st=" << st << endl;
  cout << make_tuple(1, 2, 3) << endl;
  print_bit(5);
  vector<vector<int> > mat(2, vector<int>(2));
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  mat[1][1] = 4;
  cout << "mat=" << endl;
  cout << mat << endl;
  vector<vector<int> > bit_dp(1<<2, vector<int>(5, 1));
  print_bit_dp(bit_dp);
  cmat[0][0] = 1;
  cmat[0][1] = 2;
  cmat[1][0] = 3;
  cmat[1][1] = 4;
  print_mat(2, 2, cmat);
  print(v, s);
  print(v, s, ms, mp, q, pq, dq, st);
  return 0;
}
