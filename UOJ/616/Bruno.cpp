#include "Bruno.h"
#include <vector>
#include <assert.h>
#include <iostream>
#include <bits/stdc++.h>
#define eb emplace_back
#define ep emplace

#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

#define vec vector<int>
#define ves vector<char>

using ll = long long;

const int B = 63;
const int T = 43;

namespace b {
	const int N = 1e5 + 10;
	int a[N], stk[N], top, n;
	ll fib[B + 10];
	void runit(int pos) {
		top = 0;
		rep(i, 0, n - 1) {
			if(a[i]) { while(top && stk[top] != pos) Remove(stk[top]), top--; Remove(i); }
			else stk[++top] = i;
		} while(top) Remove(stk[top--]);
	}
}  // namespace

void Bruno(int N, int L, std::vector<int> A) {
	b :: n = N; int pos = 0; rep(i, 0, 18) pos |= A[i] << i;
	b :: fib[0] = b :: fib[1] = 1; rep(i, 2, B) b :: fib[i] = b :: fib[i - 1] + b :: fib[i - 2];
	vector < int > tA; rep(i, 19, L - 1) tA.eb(A[i]); A = tA;
	vector < ll > pot; int curpos = 0;
	for(int l = 0, r = T; l <= L - 1; l += T + 1, r += T + 1) {
		ll ret = 0; per(j, r, l) ret = ret << 1 | A[j];
		vector < int > tpot;
		per(j, B, 1) if(ret >= b :: fib[j]) tpot.eb(j), ret -= b :: fib[j];
		for(auto v : tpot) b :: a[v + curpos - 1] = 1; curpos += B;
	}
	b :: runit(pos);
}
