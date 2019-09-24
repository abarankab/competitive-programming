for i in range(1, 10000):
    if 2 * i * (i + 1) * (i * i + i) != i * i + i * (i + 1) + i * (i * i + i):
        print("oh")
