# https://atcoder.jp/contests/abc207/tasks/abc207_b

A, B, C, D = map(int, input().split())

def ceil(a, b):
    return (a + b - 1) // b

d = C * D - B
if d <= 0:
    ans = -1
else:
    ans = ceil(A, d)
print(ans)
