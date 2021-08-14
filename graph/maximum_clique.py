# https://atcoder.jp/contests/abc002/tasks/abc002_4

import itertools
import sys

def main():
    N, M = map(int, sys.stdin.readline().split())
    graph = [[] for i in range(N)]
    for m in range(M):
        x, y = map(int, sys.stdin.readline().split())
        graph[x - 1].append(y - 1)
        graph[y - 1].append(x - 1)
    # Maximum clique problem
    ans = 1
    for b in range(2 ** N):
        array = []
        for n in range(N):
            if (1 << n) & b:
                array.append(n)
        if len(array) >= 2:
            ok = True
            for i, j in itertools.permutations(array, 2):
                if not (j in graph[i]):
                    ok = False
                    break
            if ok:
                ans = max(ans, len(array))
    print(ans)

if __name__ == '__main__':
    main()
