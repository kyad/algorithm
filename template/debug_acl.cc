// modint
ostream& operator<<(ostream& os, const mint &v) {
  os << v.val();
  return os;
}

// lazy_segtree
void print_segtree(lazy_segtree<S, op, e, F, mapping, composition, id> &seg, size_t N) {
  int MOD = -1;
  cout << '[';
  for (size_t i = 0; i < N; i++) {
    cout << seg.get(i);
    if (i == N - 1) {
      continue;
    } else if (MOD > 0 && (int)i % MOD == (MOD - 1)) {
      cout << '\n';
    } else {
      cout << ' ';
    }
  }
  cout << ']' << endl;
}

ostream& operator<<(ostream& os, lazy_segtree<S, op, e, F, mapping, composition, id> seg) {
  const int N = 1;
  int MOD = -1;
  os << '[';
  for (int i = 0; i < N; i++) {
    S s = seg.get(i);
    os << s;
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
