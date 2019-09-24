n, k = map(int, input().split())

l = 1
r = (1 <<n) - 1
res = n

m = (l + r) // 2

while k != m:
    res -= 1
    if k > m:
        l = m + 1
    else:
        r = m - 1
    m = (l + r) // 2

print(res)
