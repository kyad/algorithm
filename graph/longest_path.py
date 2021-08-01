# https://atcoder.jp/contests/dp/tasks/dp_g
# https://qiita.com/drken/items/03c7db44ccd27820ea0d

import sys
sys.setrecursionlimit(10**5)

INF = 10**9

N, M = map(int, input().split())
graph = [[] for n in range(N)]
for m in range(M):
    x, y = map(int, input().split())
    graph[x - 1].append(y - 1)

dp = [-INF] * N

def rec(n):
    if dp[n] >= 0:
        return dp[n]
    if not graph[n]:
        dp[n] = 0
        return dp[n]
    for e in graph[n]:
        dp[n] = max(dp[n], rec(e) + 1)
    return dp[n]

for n in range(N):
    rec(n)

print(max(dp))
