import numpy as np
import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("incorrect parameter")

    p = 1e-8
    m = int(sys.argv[1])
    print(f"madbc.py: m={m}")
    a = abs(np.random.normal(0, 1))
    d = np.random.normal(0, 1)
    b = list(np.random.normal(0, 1, m))
    c = list(np.random.normal(0, 1, m))
    with open("madbc.txt", "w") as f:
        f.write(
            f"{p}\n{m}\n{a}\n{d}\n{' '.join(str(i) for i in b)}\n{' '.join(str(i) for i in c)}\n"
        )
