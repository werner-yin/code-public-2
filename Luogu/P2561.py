n = int(input())
num = n * (n + 1) // 2
ans = 0
def qp(x, t):
    ret = 1
    while t > 0:
        if t & 1:
            ret *= x
        t >>= 1
        x *= x
    return ret

ans = qp(2, num) + qp(2, (num + 2) // 3) * 2 + qp(2, (num + (n + 1) // 2) // 2) * 3
ans //= 6
print(ans)
