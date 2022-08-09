from math import gcd
d, k = map(int,input().split())
pv = 1
tk = k
hav = 0
ohv = 0
od = d
while k % 2 == 0 and d % 2 == 0:
    k //= 2
    pv *= 2
    hav += 1

if k % 3 == 0 or k % 5 == 0 or k % 7 == 0:
    ohv = 1

while k % 3 == 0 and d % 3 == 0:
    k //= 3
    pv *= 3

while k % 5 == 0 and d % 5 == 0:
    k //= 5
    pv *= 5

while k % 7 == 0 and d % 7 == 0:
    k //= 7
    pv *= 7

if not hav:
    ohv = 0

td = 0
while d % 2 == 0:
    d //= 2
    td += 1
    hav -= 1

if td > 1:
    hav = -1

if ohv > 0 :
    hav += 1

if hav > 0:
    pv *= 2

while gcd(k, d) > 1 and k % gcd(k, d) == 0:
    pv *= gcd(k, d)
    k //= gcd(k, d)

print(pv * od)