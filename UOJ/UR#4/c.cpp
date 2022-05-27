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
using db = double;
using pii = pair < int, int >;
using vec = vector < int >;
using veg = vector < pii >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x > y ? x : y; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 5e5 + 10;
const int inf = 0x3f3f3f3f;

int n, K, p[N], a[N], b[N], c[N], w[N];
int dep[N], son[N], siz[N], top[N], dfn[N], ind[N], tim, R[N];
vec G[N];
veg pot[N];

struct node { int len, st, ed; };

bool operator < (node a, node b) { return a.len < b.len; }

void dfs(int x) {
	dep[x] = dep[p[x]] + 1; siz[x] = 1;
	for(auto y : G[x]) dfs(y), siz[x] += siz[y], son[x] = siz[y] > siz[son[x]] ? y : son[x];
}

void dfs1(int x, int anc) {
	top[x] = anc; dfn[x] = ++tim; ind[dfn[x]] = x; if(son[x]) dfs1(son[x], anc);
	for(auto y : G[x]) if(y ^ son[x]) dfs1(y, y); R[x] = tim;
}

bool intr(int x, int y) { return dfn[y] >= dfn[x] && dfn[y] <= R[x]; }

namespace seg {
	pii val[N << 2];
	void build(int o = 1, int l = 1, int r = n) {
		if(l == r) return val[o] = { w[ind[l]], ind[l] }, void(); int mid = l + r >> 1;
		build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); val[o] = min(val[o << 1], val[o << 1 | 1]);
	}
	pii query(int xl, int xr, int o = 1, int l = 1, int r = n) {
		if(xl <= l && r <= xr) return val[o]; int mid = l + r >> 1; pii ret = { inf, -1 };
		if(xl <= mid) chkmin(ret, query(xl, xr, o << 1, l, mid)); if(xr > mid) chkmin(ret, query(xl, xr, o << 1 | 1, mid + 1, r)); return ret;
	}
}

pii getmin(int st, int ed) { 
	int x = st; pii ret = { inf, -1 };
	while(top[x] != top[ed]) 
		chkmin(ret, seg :: query(dfn[top[x]], dfn[x])), x = p[top[x]];
	if(x != ed) chkmin(ret, seg :: query(dfn[ed] + 1, dfn[x])); return ret;
}

int lca(int x, int y) {
	//cerr << "!" << x << " " << y << endl;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = p[top[x]];
	} //cerr << (dep[x] > dep[y] ? y : x) << endl;
	return dep[x] > dep[y] ? y : x;
}

multiset < node > q;

void add(int x, int pr) { 
	for(auto t : pot[x]) {
		int st = t.fi, ed = t.se; pii vl = getmin(st, ed);
		q.ep((node) { pr + vl.fi, st , ed });
	}
}

void addit(int x, int y, int len) { if(x == y) return; q.ep((node) { len + getmin(x, y).fi, x, y }); }

void extend(node x) {
	pii vl = getmin(x.st, x.ed);
	add(vl.se, x.len); addit(x.st, vl.se, x.len - vl.fi), addit(p[vl.se], x.ed, x.len - vl.fi);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin); freopen("1.out", "w", stdout);
#endif
	n = in, K = in;
	rep(i, 1, n) w[i] = in;
	rep(i, 2, n) p[i] = in, G[p[i]].eb(i);
	rep(i, 1, n) a[i] = in, b[i] = in, c[i] = in;
	dfs(1); dfs1(1, 1); seg :: build();
	rep(i, 1, n) {
		int l1 = lca(a[i], b[i]), l2 = lca(b[i], c[i]), l3 = lca(c[i], a[i]);
		int t = l1, pt = t; if(dep[l2] > dep[t]) t = l2; if(dep[l3] > dep[t]) t = l3;
		for(auto v : { l1, l2, l3 }) if(v != t) pt = v;
		for(auto v : { a[i], b[i], c[i] }) if(intr(t, v)) { if(v != t) pot[i].eb(v, t); } else if(v != pt) pot[i].eb(v, pt);
		pot[i].eb(t, p[pt]); 
	}
	//rep(i, 1, n) for(auto v : pot[i]) cerr <<i << " " <<  v.fi << " " << v.se << endl;
	rep(i, 1, n) if(!G[i].size()) pot[0].eb(i, p[top[i]]); add(0, 0);
	rep(i, 1, K) {
		node cur = *q.begin(); q.erase(q.begin()); printf("%d\n", cur.len); 
		extend(cur); while(q.size() > K - i) q.erase(--q.end());
	} return 0;
}
