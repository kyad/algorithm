# https://atcoder.jp/contests/abc126/tasks/abc126_d
# https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap13/code_13_5.cpp

import sys
sys.setrecursionlimit(10 ** 5 * 2 + 1)

def dfs(graph, v, cur):
    color[v] = cur
    for next_v in graph[v]:
        if color[next_v] != -1:
            if color[next_v] == cur:
                return False
            continue
        if not dfs(graph, next_v, 1 - cur):
            return False
    return True            

N = int(input())
graph = [[] for n in range(2 * N)]
for n in range(N - 1):
    u, v, w = map(int, input().split())
    if w % 2 == 0:
        graph[u - 1].append(u - 1 + N)
        graph[u - 1 + N].append(u - 1)
        graph[u - 1 + N].append(v - 1)
        graph[v - 1].append(u - 1 + N)
    else:
        graph[u - 1].append(v - 1)
        graph[v - 1].append(u - 1)

# DFS
is_bipartite = True
color = [-1] * (2 * N)
for v in range(N):
    if color[v] != -1:
        continue
    if not dfs(graph, v, 0):
        is_bipartite = False

for v in range(N):
    print(color[v])
