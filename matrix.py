import numpy as np
import random
import time


size = 3000
array = np.empty([size, size])

for j in range(size):
    for i in range(size):
        array[j][i] = random.random() * 50

print("初期化完了")
mtx = np.matrix(array)
print("行列オブジェクト生成")


mt = None

print("行列積開始")
#測定開始
elapsedTime = 0
times = 10
for i in range(times):
    start = time.time()
    mt = mtx * mtx
    for i in range(3):
        mt = mt * mtx
    end = time.time()
    print(f"{i}回目: {end - start}秒")
    elapsedTime += end - start

#測定終了

print(f"時間 {elapsedTime/times}秒")

