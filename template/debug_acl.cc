// lazy_segtree
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
