#include <bits/stdc++.h>

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define in read<int>()
#define lin read<ll>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using vec = vector < int >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x > y ? x : y; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 2e6 + 10;
const int mod = 998244353;
const int inv2 = (mod + 1) >> 1;

int n, L, R;
vec G[N];

namespace seg {
	const int N = 1e7 + 10;
	struct node { int mul, add; } val[N];
	int ndn; vec pot; int ch[N][2];
	int nd(int _mul = 1, int _add = 0) {
		int x; if(pot.size()) x = pot.back(), pot.pop_back(); else x = ++ndn;
		val[x].mul = _mul; val[x].add = _add; ch[x][0] = ch[x][1] = 0; return x;
	}
	void pt(int o, int x, int y) {
		val[o].mul = 1ll * val[o].mul * x % mod; val[o].add = 1ll * val[o].add * x % mod;
		val[o].add = (val[o].add + y) % mod;
	}
	void pd(int o) {
		if(val[o].mul != 1 || val[o].add != 0) {
			if(!ch[o][0]) ch[o][0] = nd(val[o].mul, val[o].add); else pt(ch[o][0], val[o].mul, val[o].add);
			if(!ch[o][1]) ch[o][1] = nd(val[o].mul, val[o].add); else pt(ch[o][1], val[o].mul, val[o].add);
			val[o].mul = 1; val[o].add = 0;
		}
	}
	void upd(int xl, int xr, int x, int y, int &o, int l = 1, int r = n - 1) {
		if(!o) o = nd(); if(xl <= l && r <= xr) return pt(o, x, y); pd(o); int mid = l + r >> 1;
		if(xl <= mid) upd(xl, xr, x, y, ch[o][0], l, mid); if(xr > mid) upd(xl, xr, x, y, ch[o][1], mid + 1, r);
	}
	int query(int pos, int o, int l = 1, int r = n - 1) {
		if(!o) return 0; if(l == r) return val[o].add; pd(o); int mid = l + r >> 1;
		if(pos <= mid) return query(pos, ch[o][0], l, mid); else return query(pos, ch[o][1], mid + 1, r);
	}
	int merge(int x, int y) {
		if(!ch[x][0] && !ch[x][1]) return pt(y, val[x].add, 0), pot.eb(x), y;
		if(!ch[y][0] && !ch[y][1]) return pt(x, val[y].add, 0), pot.eb(y), x;
		pd(x); pd(y); ch[x][0] = merge(ch[x][0], ch[y][0]); ch[x][1] = merge(ch[x][1], ch[y][1]); pot.eb(y); return x;
	}
}

const int inf = 0x3f3f3f3f;

int val[N], tp[N], ans[N], rt[N];
ll ret = 1;

void dfs(int x, int p) {
	tp[x] = tp[p] ^ 1; val[x] = tp[x] ? 0 : inf; bool hav = false;
	for(auto y : G[x]) if(y ^ p) {
			dfs(y, x); hav = true;
			if(tp[x]) chkmax(val[x], val[y]);
			else chkmin(val[x], val[y]);
		}
	if(!hav) val[x] = x, ret = (ret + ret) % mod;
}

void vdfs(int x, int p, int rftp) {
	if(val[x] == x) {
		if(rftp ? val[x] < val[1] : val[x] > val[1]) { // 主链上面的是 1 类点，那么只有当这个叶子权值小于 W，就会根本不可能改变根的权值。
			int k = abs(val[x] - val[1]); 
			seg :: upd(1, k, 0, (tp[x] ? val[x] < val[1] : val[x] > val[1]), rt[x]);
			seg :: upd(k + 1, n - 1, 0, inv2, rt[x]);
		} else seg :: upd(1, n - 1, 0, (tp[x] ? val[x] < val[1] : val[x] > val[1]), rt[x]);
		return;
	}
	seg :: upd(1, n - 1, 0, 1, rt[x]);
	for(auto y : G[x]) if(y ^ p) {
			vdfs(y, x, rftp); seg :: upd(1, n - 1, mod - 1, 1, rt[y]);
			rt[x] = seg :: merge(rt[x], rt[y]);
		}
}

void tdfs(int x, int p) {
	seg :: upd(1, n - 1, 0, val[x] == x ? inv2 : 1, rt[x]);
	for(auto y : G[x]) if(y ^ p) {
			if(val[x] == val[y]) tdfs(y, x), rt[1] = seg :: merge(rt[1], rt[y]);
			else 
				vdfs(y, x, tp[x]), seg :: upd(1, n - 1, mod - 1, 1, rt[y]), rt[x] = seg :: merge(rt[x], rt[y]);
		}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin); freopen("3044.out", "w", stdout);
#endif
	n = in, L = in, R = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v); G[v].eb(u); }
	dfs(1, 0); tdfs(1, 0); rep(i, max(L - 1, 1), min(n, R)) ans[i] = (mod + 1 - seg :: query(i, rt[1])) % mod * ret % mod;
	ans[n] = ret - 1;
	per(i, R, L) ans[i] = (ans[i] + mod - ans[i - 1]) % mod; rep(i, L, R) printf("%d ", ans[i]); puts(""); return 0;
}
