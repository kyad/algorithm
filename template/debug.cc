#include <iostream>
#include <queue>
#include <set>
#include <stack>
using namespace std;

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

// pair
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1, T2> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

// vector
template<class T> ostream& operator<<(ostream& os, const vector<T> &v) {
  size_t N = v.size();
  int MOD = 5;
  os << '[';
  for (size_t i = 0; i < N; i++) {
    os << v[i];
    if (i % MOD == (MOD - 1)) {
      os << '\n';
    } else if (i != N - 1) {
      os << ' ';
    }
  }
  os << ']';
  return os;
}

// 2d-matrix
template<class T> ostream& operator<<(ostream& os, const vector<vector<T> > &v) {
  size_t y0 = 0;
  size_t y1 = v.size() - 1;
  for (size_t i = y0; i <= y1; i++) {
    os << (i == 0 ? "[[" : " [");
    size_t x0 = 0;
    size_t x1 = v[i].size() - 1;
    for (size_t j = x0; j <= x1; j++) {
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

// set
template<class T> ostream& operator<<(ostream& os, const set<T> &s) {
  os << '[';
  for (typename set<T>::iterator it = s.begin(); it != s.end(); it++) {
    os << *it;
    if (it != prev(s.end())) {
      os << ' ';
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

int cmat[10][2000];
int main() {
  print_bit(5);
  cout << make_pair(1, 2) << endl;
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  cout << "v=" << v << endl;
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
  set<int> s;
  s.insert(1);
  s.insert(2);
  cout << "s=" << s << endl;
  multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  cout << "ms=" << ms << endl;
  queue<int> q;
  q.push(1);
  q.push(2);
  cout << "q=" << q << endl;
  deque<int> dq;
  dq.push_front(1);
  dq.push_back(2);
  cout << "dq=" << dq << endl;
  stack<int> st;
  st.push(1);
  st.push(2);
  cout << "st=" << st << endl;
  return 0;
}
