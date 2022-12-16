import numpy as np

p = 1e-8
m = 100000
a = abs(np.random.normal(0, 1))
d = np.random.normal(0, 1)
b = list(np.random.normal(0, 1, m))
c = list(np.random.normal(0, 1, m))
with open("madbc.txt", "w") as f:
    f.write(
        f"{p}\n{m}\n{a}\n{d}\n{' '.join(str(i) for i in b)}\n{' '.join(str(i) for i in c)}\n"
    )
