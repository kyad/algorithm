# https://atcoder.jp/contests/arc005/tasks/arc005_3
# https://drken1215.hatenablog.com/entry/2021/07/30/024800
# https://betrue12.hateblo.jp/entry/2018/12/08/000020

from collections import deque

H, W = map(int, input().split())
c = [input() for h in range(H)]
for y in range(H):
    for x in range(W):
        if c[y][x] == 's':
            start_y, start_x = y, x
        elif c[y][x] == 'g':
            goal_y, goal_x = y, x
# 01-BFS
INF = 500 * 500 + 1
dist = [INF] * (H * W)
dq = deque()
dist[start_y * W + start_x] = 0
dq.append(start_y * W + start_x)
while len(dq) > 0:
    min_dist_idx = dq.popleft()
    y = min_dist_idx // W
    x = min_dist_idx % W
    for dy, dx in zip((0, -1, 0, 1), (-1, 0, 1, 0)):
        yy = y + dy
        xx = x + dx
        if 0 <= yy < H and 0 <= xx < W:
            if c[yy][xx] == '#':  # cost=1
                if dist[yy * W + xx] > dist[y * W + x] + 1:
                    dist[yy * W + xx] = dist[y * W + x] + 1
                    dq.append(yy * W + xx)
            else:  # cost=0
                if dist[yy * W + xx] > dist[y * W + x]:
                    dist[yy * W + xx] = dist[y * W + x]
                    dq.appendleft(yy * W + xx)
print('YES' if dist[goal_y * W + goal_x] <= 2 else 'NO')
