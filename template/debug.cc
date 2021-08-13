// Print vector
template<class T> ostream& operator<<(ostream& os, const vector<T> &v) {
  os << '[';
  for (size_t i = 0; i < v.size(); i++) {
    os << v[i] << (i == v.size() - 1 ? ']' : ' ');
  }
  return os;
}

// Print 2d-matrix
template<class T> ostream& operator<<(ostream& os, const vector<vector<T> > &v) {
  for (size_t i = 0; i < v.size(); i++) {
    os << (i == 0 ? "[[" : " [");
    for (size_t j = 0; j < v[i].size(); j++) {
      os << v[i][j] << (j == v[i].size() - 1 ? ']' : ' ');
    }
    os << (i == v.size() - 1 ? ']' : '\n');
  }
  return os;
}
