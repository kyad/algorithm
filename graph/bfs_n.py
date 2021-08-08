# https://atcoder.jp/contests/abc132/tasks/abc132_e
# https://drken1215.hatenablog.com/entry/2019/07/01/111500

import queue

def bfs(graph, S):
    N = len(graph)
    dist = [[-3] * 3 for n in range(N)]
    q = queue.Queue()
    dist[S][0] = 0
    q.put((S, 0))
    while not q.empty():
        v, parity = q.get()
        for nv in graph[v]:
            np = (parity + 1) % 3
            if dist[nv][np] >= 0:
                continue
            dist[nv][np] = dist[v][parity] + 1
            q.put((nv, np))
    return dist

N, M = map(int, input().split())
graph = [[] for n in range(N)]
for m in range(M):
    u, v = map(int, input().split())
    graph[u - 1].append(v - 1)
S, T = map(int, input().split())

dist = bfs(graph, S - 1)

print(dist[T - 1][0] // 3)
