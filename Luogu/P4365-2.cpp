#include <bits/stdc++.h>

#define eb emplace_back
#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using uint = unsigned int;
using pii = pair < int, int >;
using vec = vector < int >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = 2010;
const int mod = 64123;

int n, K, W, d[N];
vec G[N];

struct node { // (f, g) -> (af + b, cf + d + g)
	uint a, b, c, d;
	node(uint _a = 1, uint _b = 0, uint _c = 0, uint _d = 0) : a(_a), b(_b), c(_c), d(_d) { }
};

node operator + (node x, node y) {
	node z;
	z.a = x.a * y.a % mod; z.b = (x.b * y.a + y.b) % mod;
	z.c = (x.a * y.c + x.c) % mod; z.d = (x.b * y.c + x.d + y.d) % mod;
	return z;
}
void operator += (node &x, const node &y) { x = x + y; }

namespace seg {
	const int N = 1e7 + 10;
	node val[N];
	int ch[N][2], ndn;
	vec pot;
	int nd() {
		int x; if(pot.size()) x = pot.back(), pot.pop_back(); else x = ++ndn;
		ch[x][0] = ch[x][1] = 0; val[x] = node(); return x;
	}
	void pd(const int &x) {
		if(!ch[x][0]) ch[x][0] = nd(); if(!ch[x][1]) ch[x][1] = nd();
		if(val[x].a == 1 && val[x].b == 0 && val[x].c == 0 && val[x].d == 0) return;
		val[ch[x][0]] += val[x]; val[ch[x][1]] += val[x]; val[x] = node();
	}
	void upd(const int &xl, const int &xr, const node &v, int &o, const int &l = 1, const int &r = W) {
		if(!o) o = nd(); if(xl <= l && r <= xr) return val[o] += v, void(); int mid = l + r >> 1; pd(o);
		if(xl <= mid) upd(xl, xr, v, ch[o][0], l, mid); if(xr > mid) upd(xl, xr, v, ch[o][1], mid + 1, r);
	}
	uint get(const int &o, int l = 1, int r = W) {
		if(l == r) return val[o].d; int mid = l + r >> 1; pd(o);
		return (get(ch[o][0], l, mid) + get(ch[o][1], mid + 1, r)) % mod;
	}
	int merge(int x, int y) {
		if(!x || !y) return x | y; if(!ch[x][0] && !ch[x][1]) swap(x, y);
		if(!ch[y][0] && !ch[y][0]) return val[x] += node(val[y].b, 0, 0, 0), val[x] += node(1, 0, 0, val[y].d), pot.eb(y), x;
		pd(x); pd(y); ch[x][0] = merge(ch[x][0], ch[y][0]); ch[x][1] = merge(ch[x][1], ch[y][1]); pot.eb(y); return x;
	}
	void reset() { pot.clear(); ndn = 0; }
} int rt[N];

uint inv[N], res[N], f[N], g[N], ans;

void dfs(int x, int p, int tval) {
	rt[x] = 0; seg :: upd(1, W, node(0, 1, 0, 0), rt[x]);
	for(auto y : G[x]) if(y ^ p) {
			dfs(y, x, tval);
			rt[x] = seg :: merge(rt[x], rt[y]);
		}
	seg :: upd(1, d[x], node(tval, 0, 0, 0), rt[x]);
	seg :: upd(1, W, node(1, 0, 1, 0), rt[x]);
	seg :: upd(1, W, node(1, 1, 0, 0), rt[x]);
}

void Lagrange() {
	f[0] = 1; rep(i, 1, n + 1) per(j, n + 1, 0) f[j] = (f[j] * (mod - i) % mod + (j == 0 ? 0 : f[j - 1])) % mod;
	rep(i, 1, n + 1) {
		rep(j, 0, n + 1) g[j] = f[j];
		rep(j, 0, n + 1) {
			g[j] = (mod - g[j] * inv[i] % mod) % mod;
			g[j + 1] = (g[j + 1] + mod - g[j]) % mod;
		}
		uint tres = 0; rep(k, K, n) tres = (tres + g[k]) % mod;
		rep(j, 1, n + 1) if(i ^ j) tres = tres * (j < i ? inv[i - j] : mod - inv[j - i]) % mod;
		ans = (ans + tres * res[i] % mod) % mod;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in, W = in; rep(i, 1, n) d[i] = in;
	rep(i, 2, n) { int u = in, v = in; G[u].eb(v); G[v].eb(u); }
	inv[1] = 1; rep(i, 2, n + 1) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	rep(i, 1, n + 1) { seg :: reset(); dfs(1, 0, i); res[i] = seg :: get(rt[1]); }
	Lagrange(); printf("%u\n", ans);
	return 0;
}
