# https://atcoder.jp/contests/abc217/tasks/abc217_b

s = set()
s.add('ABC')
s.add('ARC')
s.add('AGC')
s.add('AHC')
for i in range(3):
    s.remove(input())
print(s.pop())
