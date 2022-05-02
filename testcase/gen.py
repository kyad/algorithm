import random
N = 3
L = 4
word = [chr(ord('a') + i) for i in range(5)]

print(N, L)

for n in range(N):
    a = sorted(random.sample(word, 3))  # 重複しないように選ぶ
    print(''.join(a))
