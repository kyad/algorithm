# https://atcoder.jp/contests/abc075/tasks/abc075_c
# https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap11/code_11_1.cpp
# https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap11/code_11_4.cpp

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


N, M = map(int, input().split())
graph = []
for m in range(M):
    a, b = map(int, input().split())
    graph.append((a - 1, b - 1))

ans = 0
for m in range(M):
    uf = UnionFind(N)
    for e in range(M):
        if m == e:
            continue
        uf.unite(graph[e][0], graph[e][1])
    count = 0
    for n in range(N):
        if uf.root(n) == n:
            count += 1
    if count == 2:
        ans += 1

print(ans)
