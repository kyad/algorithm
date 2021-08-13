# https://atcoder.jp/contests/jag2012autumn/tasks/icpc2012autumn_c
# https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap11/code_11_1.cpp
# https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap11/code_11_4.cpp
# https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap15/code_15_1.cpp

import sys

class UnionFind:
    def __init__(self, N):
        self.parent = [-1] * N
        self._size = [1] * N

    def root(self, x):
        if self.parent[x] == -1:
            return x;
        else:
            ans = self.root(self.parent[x])
            self.parent[x] = self.root(self.parent[x])
            return ans

    def issame(self, x, y):
        return self.root(x) == self.root(y)

    def unite(self, x, y):
        x = self.root(x)
        y = self.root(y)
        if x == y:
            return False
        else:
            if self._size[x] < self._size[y]:
                x, y = y, x  # Union by size
            self.parent[y] = x
            self._size[x] += self._size[y]
            return True

    def size(self, x):
        return self._size[self.root(x)]


def main(n, m):
    edges = []
    for i in range(m):
        s, t, c = map(int, sys.stdin.readline().split())
        edges.append((c, s - 1, t - 1))
    edges.sort()
    # Kruskal's algorithm O(|E|log|V|)
    weights = []
    uf = UnionFind(n)
    for w, u, v in edges:
        if uf.issame(u, v):
            continue
        weights.append(w)
        uf.unite(u, v)
    print(weights[n // 2 - 1])        

if __name__ == '__main__':
    while True:
        n, m = map(int, sys.stdin.readline().split())
        if n == 0 and m == 0:
            exit(0)
        main(n, m)
