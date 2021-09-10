// pair
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1, T2> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

// vector
template<class T> ostream& operator<<(ostream& os, const vector<T> &v) {
  os << '[';
  for (size_t i = 0; i < v.size(); i++) {
    os << v[i] << (i == v.size() - 1 ? ']' : ' ');
  }
  return os;
}

// 2d-matrix
template<class T> ostream& operator<<(ostream& os, const vector<vector<T> > &v) {
  for (size_t i = 0; i < v.size(); i++) {
    os << (i == 0 ? "[[" : " [");
    for (size_t j = 0; j < v[i].size(); j++) {
      os << v[i][j];
      if (j != v[i].size() - 1) {
        os << ' ';
      }
    }
    os << (i == v.size() - 1 ? "]]" : "]\n");
  }
  return os;
}

// 2d-matrix (C)
#include <iomanip>
void print_mat(int h, int w, long long a[][2000]) {
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

// multiset
template<class T> ostream& operator<<(ostream& os, const multiset<T> &ms) {
  for (typename multiset<T>::iterator it = ms.begin(); it != ms.end(); it++) {
    os << *it;
    if (it != prev(ms.end())) {
      os << ' ';
    }
  }
  return os;
}

// deque
template<class T> ostream& operator<<(ostream& os, const deque<T> &dq) {
  for (auto it = dq.begin(); it != dq.end(); it++) {
    os << *it;
    if (it != prev(dq.end())) {
      os << ' ';
    }
  }
  return os;
}
