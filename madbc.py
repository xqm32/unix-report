import numpy as np

m = 100000
a = abs(np.random.normal(0, 1))
d = np.random.normal(0, 1)
b = list(np.random.normal(0, 1, m))
c = list(np.random.normal(0, 1, m))
with open("madbc.txt", "w") as f:
    f.write(
        f"{m}\n{a}\n{d}\n{' '.join(str(i) for i in b)}\n{' '.join(str(i) for i in c)}\n"
    )
