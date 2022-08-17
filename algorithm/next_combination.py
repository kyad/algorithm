# https://atcoder.jp/contests/abc263/tasks/abc263_c

import itertools

N, M = map(int, input().split())

l = [ i + 1 for i in range(M) ]
for a in itertools.combinations(l, N):
    print(*a, sep=' ')
