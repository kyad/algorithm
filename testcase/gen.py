import random

# N = random.randint(a, b)  # a<=N<=b のNを返す

# alphabet = ''.join([chr(ord('a') + i) for i in range(26)])
# S = ''.join(random.choices(alphabet, k=len))  # ランダムな文字列

N = 3
L = 4
word = [chr(ord('a') + i) for i in range(5)]

print(N, L)

for n in range(N):
    # a = random.sample(l, k=k)  # 重複を許さない
    # a = random.choices(l, k=k)  # 重複を許す
    a = sorted(random.sample(word, 3))  # 重複しないように選ぶ
    print(''.join(a))
