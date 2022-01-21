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

struct node { // (f, g) -> (a * f + b, c * f + g + d)
	uint a, b, c, d;
	node(uint _a = 1, uint _b = 0, uint _c = 0, uint _d = 0) : a(_a), b(_b), c(_c), d(_d) { }
	void out() { cerr << a << " " << b << " " << c << " " << d << endl; }
};
node operator + (node x, node y) {
	node z;	z.a = x.a * y.a % mod;
	z.b = (x.b * y.a + y.b) % mod; z.c = (x.a * y.c + x.c) % mod;
	z.d = (x.b * y.c + x.d + y.d) % mod; return z;
}

namespace seg {
	const int N = 1e7 + 10;
	node val[N]; int ch[N][2], ndn;
	vec pot;
	int nd() {
		int x; if(pot.size()) x = pot.back(), pot.pop_back(); else x = ++ndn;
		ch[x][0] = ch[x][1] = 0; val[x] = node(); return x;
	}
	void pd(int o) {
		if(!ch[o][0]) ch[o][0] = nd(); if(!ch[o][1]) ch[o][1] = nd();
		val[ch[o][0]] = val[ch[o][0]] + val[o]; val[ch[o][1]] = val[ch[o][1]] + val[o];
		val[o] = node();
	}
	void upd(int xl, int xr, node v, int &o, int l = 1, int r = W) {
		if(!o) o = nd(); if(xl == l && xr == r) return val[o] = val[o] + v, void(); pd(o); int mid = l + r >> 1;
		if(xr <= mid) upd(xl, xr, v, ch[o][0], l, mid); else if(xl > mid) upd(xl, xr, v, ch[o][1], mid + 1, r);
		else upd(xl, mid, v, ch[o][0], l, mid), upd(mid + 1, xr, v, ch[o][1], mid + 1, r);
	}
	uint get(int o, int l = 1, int r = W) {
		if(l == r) return val[o].d; int mid = l + r >> 1; pd(o);
		return (get(ch[o][0], l, mid) + get(ch[o][1], mid + 1, r)) % mod;
	}
	void reset() { pot.clear(); ndn = 0; }
	int merge(int x, int y) {
		if(!x || !y) return x | y; if(!ch[x][0] && !ch[x][1]) swap(x, y);
		if(!ch[y][0] && !ch[y][1])
			return val[x] = val[x] + node(val[y].b, 0, 0, 0), val[x] = val[x] + node(1, 0, 0, val[y].d), pot.eb(y), x;
		pd(x); pd(y); ch[x][0] = merge(ch[x][0], ch[y][0]); ch[x][1] = merge(ch[x][1], ch[y][1]);
		pot.eb(y); return x;
	}
} int rt[N];

void dfs(int x, int p, int tval) {
	rt[x] = 0; seg :: upd(1, W, node(0, 1, 0, 0), rt[x]); // initial
	for(auto y : G[x])
		if(y ^ p) {
			dfs(y, x, tval);
			rt[x] = seg :: merge(rt[x], rt[y]);
		}
	seg :: upd(1, d[x], node(tval, 0, 0, 0), rt[x]); // *x^{1}
	seg :: upd(1, W, node(1, 0, 1, 0), rt[x]); // g += f
	seg :: upd(1, W, node(1, 1, 0, 0), rt[x]); // f += 1, empty set
}

uint res[N], f[N], g[N], inv[N], ans;

void Lagrange() {
	f[0] = 1; rep(i, 1, n + 1) per(j, n + 1, 0) f[j] = (f[j] * (mod - i) % mod + (j == 0 ? 0 : f[j - 1])) % mod;
	rep(i, 1, n + 1) {
		rep(j, 0, n + 1) g[j] = f[j];
		rep(j, 0, n + 1) {
			g[j] = (mod - g[j] * inv[i] % mod) % mod;
			g[j + 1] = (g[j + 1] + mod - g[j]) % mod;
		} // g : current dp value.
		uint tres = 0; rep(j, K, n) (tres += g[j]) %= mod;
		//cerr << tres << " " << res[i] << endl;
		rep(j, 1, n + 1) if(i ^ j) tres = tres * (j < i ? inv[i - j] : mod - inv[j - i]) % mod;
		ans = (ans + tres * res[i]) % mod;
	} 
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in, W = in;
	rep(i, 1, n) d[i] = in;
	rep(i, 2, n) { int u = in, v = in; G[u].eb(v); G[v].eb(u); }
	inv[1] = 1; rep(i, 2, n + 1) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
	rep(i, 1, n + 1) { seg :: reset(), dfs(1, 0, i), res[i] = seg :: get(rt[1]); }
	Lagrange(); printf("%u\n", ans);
	return 0;
}
