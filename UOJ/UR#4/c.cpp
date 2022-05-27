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

int n, K, p[N], w[N];
int dep[N], son[N], siz[N], top[N], dfn[N], ind[N], tim, tot[N], ed[N], rt[N];
int h[N], cnt;
struct edge { int v, nxt; } e[N];
void link(int x, int y) { e[++cnt] = (edge) { y, h[x] }; h[x] = cnt; }
tuple < int, int, int > pot[N][4];

struct node { int len, st, ed; };

int tmin(int x, int y) { return x == 0 || y == 0 ? x | y : w[x] < w[y] ? x : y; }

bool operator < (node a, node b) { return a.len > b.len; }

void dfs(int x) {
	dep[x] = dep[p[x]] + 1; siz[x] = 1;
	for(int i = h[x], y = e[i].v; i; i = e[i].nxt, y = e[i].v) dfs(y), siz[x] += siz[y], son[x] = siz[y] > siz[son[x]] ? y : son[x];
}

bool intr(int x, int y) { return dfn[y] >= dfn[x] && dfn[y] <= siz[x] + dfn[x] - 1; }

namespace seg {
	int val[N << 1]; int ndn, ch[N << 1][2];
	void build(int &o, int l, int r) {
		o = ++ndn; if(l == r) return val[o] = ind[l], void(); int mid = l + r >> 1;
		build(ch[o][0], l, mid); build(ch[o][1], mid + 1, r); val[o] = tmin(val[ch[o][0]], val[ch[o][1]]);
	}
    int query(int xl, int xr, int o, int l, int r) {
		if(xl <= l && r <= xr) return val[o]; int mid = l + r >> 1; int ret = 0;
		if(xl <= mid) ret = tmin(ret, query(xl, xr, ch[o][0], l, mid)); if(xr > mid) ret = tmin(ret, query(xl, xr, ch[o][1], mid + 1, r)); return ret;
	}
}

void dfs1(int x, int anc) {
	top[x] = anc; dfn[x] = ++tim; ind[dfn[x]] = x; if(son[x]) dfs1(son[x], anc);
	for(int i = h[x], y = e[i].v; i; i = e[i].nxt, y = e[i].v) if(y ^ son[x]) dfs1(y, y);
	if(!h[x]) seg :: build(rt[top[x]], dfn[top[x]], dfn[x]), ed[top[x]] = dfn[x];
}

int getmin(int st, int ed) { 
	int x = st; int ret = 0;
	while(top[x] != top[ed]) 
		ret = tmin(ret, seg :: query(dfn[top[x]], dfn[x], rt[top[x]], dfn[top[x]], ::ed[top[x]])), x = p[top[x]];
	if(x != ed) ret = tmin(ret, seg :: query(dfn[ed] + 1, dfn[x], rt[top[x]], dfn[top[x]], ::ed[top[x]])); return ret;
}

int lca(int x, int y) {
	//cerr << "!" << x << " " << y << endl;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = p[top[x]];
	} //cerr << (dep[x] > dep[y] ? y : x) << endl;
	return dep[x] > dep[y] ? y : x;
}

//multiset < node > q;

namespace heap {
	node t[N * 15]; int siz;
	void emplace(node v) { if(v.len > 1e8) return; t[++siz] = v; push_heap(t + 1, t + siz + 1); }
	node top() { return t[1]; }
	void pop() { pop_heap(t + 1, t + siz + 1); siz--; }
}

void add(int x, int pr) { 
	rep(i, 0, tot[x] - 1) {
		auto t = pot[x][i]; int st = get<0>(t), ed = get<1>(t), v = get<2>(t);
		heap :: ep((node) { pr + v, st , ed });
	}
}

void addit(int x, int y, int len) { if(x == y) return; heap :: ep((node) { len + w[getmin(x, y)], x, y }); }

void extend(node x) {
	int vl = getmin(x.st, x.ed);
	add(vl, x.len); addit(x.st, vl, x.len - w[vl]), addit(p[vl], x.ed, x.len - w[vl]);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin); freopen("1.out", "w", stdout);
#endif
	n = in, K = in;
	rep(i, 1, n) w[i] = in;
	rep(i, 2, n) p[i] = in, link(p[i], i);
	dfs(1); dfs1(1, 1);
	rep(i, 1, n) {
		int a = in, b = in, c = in;
		int l1 = lca(a, b), l2 = lca(b, c), l3 = lca(c, a);
		int t = l1, pt = t; if(dep[l2] > dep[t]) t = l2; if(dep[l3] > dep[t]) t = l3;
		for(auto v : { l1, l2, l3 }) if(v != t) pt = v;
		for(auto v : { a, b, c })
			if(intr(t, v)) { if(v != t) pot[i][tot[i]++] = { v, t, w[getmin(v, t)] }; }
			else if(v != pt) pot[i][tot[i]++] = { v, pt, w[getmin(v, pt)] };
		pot[i][tot[i]++] = { t, p[pt], w[getmin(t, p[pt])] }; 
	}
	//rep(i, 1, n) for(auto v : pot[i]) cerr <<i << " " <<  v.fi << " " << v.se << endl;
	rep(i, 1, n) if(!h[i]) addit(i, p[top[i]], 0);
	rep(i, 1, K) {
		node cur = heap :: top(); heap :: pop(); printf("%d\n", cur.len); 
		extend(cur); //while(q.size() > K - i) q.erase(--q.end());
	} return 0;
}
