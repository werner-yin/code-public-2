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

const int N = 1e5 + 10;
const int inf = 0x3f3f3f3f;

vector < tuple < int, int, int > > fined;
int fa[N], w[N], n;
int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }
vec pot, vpot;
pii nerest[N];

namespace T2 {
	veg G[N];
	int siz[N], son[N], tfa[N], top[N], dep[N], tim, tdep[N], stk[N], ptop, dfn[N];
	void dfs(int x, int p) {
		tfa[x] = p; dep[x] = dep[p] + 1; siz[x] = 1;
		for(auto v : G[x])
			if(v.fi ^ p) tdep[v.fi] = tdep[x] + v.se, dfs(v.fi, x), siz[x] += siz[v.fi], son[x] = siz[v.fi] > siz[son[x]] ? v.fi : son[x];
	}
	void dfs1(int x, int anc) {
		top[x] = anc; dfn[x] = ++tim; if(son[x]) dfs1(son[x], anc);
		for(auto v : G[x]) if(v.fi ^ son[x] && v.fi ^ tfa[x]) dfs1(v.fi, v.fi);
	}
	int lca(int x, int y) {
		while(top[x] ^ top[y]) {
			if(dep[top[x]] < dep[top[y]]) swap(x, y);
			x = tfa[top[x]];
		} return dep[x] < dep[y] ? x : y;
	}
	int dis(int x, int y) { return tdep[x] + tdep[y] - 2 * tdep[lca(x, y)]; }
	void init() {
		rep(i, 2, n) { int u = in, v = in, w = in; G[u].eb(v, w), G[v].eb(u, w); }
		dfs(1, 0), dfs1(1, 1); rep(i, 1, n) G[i].clear();
	}
	void link(int x, int y) { G[x].eb(y, dis(x, y)); }
	struct node {
		pii x, y; int col;
		node() { x = y = { inf, 0 }; col = 0; }
		friend node operator + (node a, node b) {
			node c;
			if(a.col == b.col) {
				c.col = a.col; if(a.x > b.x) swap(a, b);
				c.x = a.x, c.y = min(a.y, b.y);
			} else {
				if(a.x > b.x) swap(a, b);
				c.col = a.col; c.x = a.x;
				c.y = min(a.y, b.x);
			} return c;
		}
		pii get(int c) { return col == c ? y : x; }
	} f[N];
	vector < tuple < int, int, int > > al;
	void pdfs(int x) {
		f[x].col = gf(x); f[x].x = { w[x], x };
		for(auto v : G[x]) {
			int y, w; tie(y, w) = v; pdfs(y);
			f[y].x.fi += w; f[y].y.fi += w; f[x] = f[x] + f[y];
			f[y].x.fi -= w; f[y].y.fi -= w;
		}
	}
	void rdfs(int x) {
		for(auto v : G[x]) {
			int y, w; tie(y, w) = v;
			f[x].x.fi += w; f[x].y.fi += w; f[y] = f[y] + f[x];
			f[x].x.fi -= w; f[x].y.fi -= w; rdfs(y);
		}
	}
	void getmst() {
		sort(vpot.begin(), vpot.end()); vpot.resize(unique(vpot.begin(), vpot.end()) - vpot.begin());
		for(auto v : vpot) fa[v] = v; bool fl = true;
		//		for(auto v : vpot) cerr << v << " " << w[v] << endl;
		//		cerr << endl;
		while(fl) {
			fl = false; for(auto v : vpot) f[v] = node(),nerest[v] = {inf, 0};
			al.clear(); pdfs(1); rdfs(1); 
			for(auto v : vpot) 
				if(w[v] < inf) {
					pii ner = f[v].get(gf(v)); ner.fi += w[v];
					if(ner.se != 0) chkmin(nerest[gf(v)], ner);
                }
            for(auto v : vpot) if(gf(v) == v && nerest[v].se != 0) 
                al.eb(nerest[v].fi, v, nerest[v].se);
			for(auto v : al) {
				int w, x, y; tie(w, x, y) = v; if(gf(x) == gf(y)) continue; fl = true;
				/*cerr << "ADDE: " << w << " " << x << " " << y << endl; */fined.eb(w, x, y); fa[gf(x)] = gf(y);
			} //cerr << "-------" << endl;
		} for(auto v : vpot) G[v].clear();
	}
	int tg, vis[N];
	void solve() {
		vpot.clear(); if(pot.size() == 1) return; sort(pot.begin(), pot.end(), [](auto x, auto y) { return dfn[x] < dfn[y]; });
		stk[ptop = 1] = 1; vpot.eb(1);
		tg++; for(auto v : pot) vis[v] = tg;
		for(auto x : pot) {
			if(x == 1) continue; int t = lca(x, stk[ptop]);
			while(dep[t] <= dep[stk[ptop - 1]]) link(stk[ptop - 1], stk[ptop]), ptop--;
			if(t != stk[ptop]) vpot.eb(t), link(t, stk[ptop]), stk[ptop] = t;
			stk[++ptop] = x;
		} rep(i, 2, ptop) link(stk[i - 1], stk[i]);
		for(auto v : vpot) if(vis[v] != tg) w[v] = inf; for(auto v : pot) vpot.eb(v); getmst();
	}
}

namespace T1 {
	veg G[N];
	int siz[N], son[N];
	bool vis[N];
	void init() { rep(i, 2, n) { int u = in, v = in, w = in; G[u].eb(v, w), G[v].eb(u, w); } }
	void gsz(int x, int p) {
		siz[x] = 1; son[x] = 0;
		for(auto v : G[x]) if(v.fi ^ p && !vis[v.fi]) gsz(v.fi, x), siz[x] += siz[v.fi], chkmax(son[x], siz[v.fi]);
	}
	int RT;
	void grt(int x, int p, int tsz) {
		chkmax(son[x], tsz - siz[x]); if(RT == 0 || son[x] < son[RT]) RT = x;
		for(auto v : G[x]) if(v.fi ^ p && !vis[v.fi]) grt(v.fi, x, tsz);
	}
	void dfs(int x, int p, int dis) {
		pot.eb(x); w[x] = dis;
		for(auto v : G[x]) if(v.fi ^ p && !vis[v.fi]) dfs(v.fi, x, dis + v.se);
	}
	void divide(int x) {
		gsz(x, 0); RT = 0; grt(x, 0, siz[x]); x = RT; vis[x] = true; 
		pot.clear(); dfs(x, 0, 0); T2 :: solve(); for(auto v : G[x]) if(!vis[v.fi]) divide(v.fi);
	}
	void solve() { divide(1); }
}

int main() {
	n = in; T1 :: init(); T2 :: init(); T1 :: solve();
	sort(fined.begin(), fined.end()); rep(i, 1, n) fa[i] = i; ll ans = 0;
	for(auto v : fined) {
		int w, x, y; tie(w, x, y) = v;
		if(gf(x) != gf(y)) fa[gf(x)] = gf(y), ans += w;
	} printf("%lld\n", ans); return 0;
}
