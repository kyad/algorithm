// Print vector
template<class T> ostream& operator<<(ostream& os, const vector<T> &v) {
  os << '[';
  for (size_t i = 0; i < v.size(); i++) {
    os << v[i] << (i == v.size() - 1 ? ']' : ' ');
  }
  return os;
}
