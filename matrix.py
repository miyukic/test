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
start = time.time()

mt = mtx * mtx
for i in range(3):
    mt = mt * mtx

#測定終了
end = time.time()

elapsedTime = end - start
print(f"時間 {elapsedTime}")

