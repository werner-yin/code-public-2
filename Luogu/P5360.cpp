#include <bits/stdc++.h>

#define eb emplace_back
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using pii = pair < int, int >;
using veg = vector < pii >;

const int N = 110, M = 10010;

int a[M][N], b[M][N], n, m, id[N * M], fa[N * M];
bool label[N * M];
vector < tuple < int, int, int > > g;
vector < pii > G[N * M];
unsigned int SA, SB, SC;int lim;
int getweight() {
	SA ^= SA << 16; SA ^= SA >> 5; SA ^= SA << 1;
	unsigned int t = SA; SA = SB; SB = SC; SC ^= t ^ SA;
	return SC % lim + 1;
}
void gen() {
	scanf("%d%d%u%u%u%d", &n, &m, &SA, &SB, &SC, &lim);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[j][i] = getweight();
	for(int i = 1; i <  n; i++) for(int j = 1; j <= m; j++) b[j][i] = getweight();
}

struct MST {
	vector < tuple < int, int, int > > E; int siz; ll res;
	MST(int *a) {
		E.clear(); rep(i, 1, n - 1) E.eb(a[i], i, i + 1);
		siz = n; res = 0;
	} MST() { E.clear(); siz = 0; res = 0; }
	ll getans() {
		ll ans = res; for(auto v : E) ans += get<0>(v);
		return ans;
	}
} pre[M], suf[M];

int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }

void dfs(int x, int p) {
	int tot = 0;
	for(auto v : G[x]) {
		int y, w; tie(y, w) = v;
		if(y ^ p) dfs(y, x), tot++;
	} label[x] |= tot >= 2;
}

ll tres;

void vdfs(int x, int p, int pre, int mx) {
	if(label[x]) {
		if(pre) g.eb(mx, id[pre], id[x]), tres -= mx;
		mx = 0; pre = x;
	} int tot = 0;
	for(auto v : G[x]) {
		int y, w; tie(y, w) = v;
		if(y ^ p) tot++, tres += w, vdfs(y, x, pre, max(mx, w));
	} 
}

MST merge(const MST &a, const MST &b, int *t) {
	MST c; c.siz = a.siz + b.siz; c.res = a.res + b.res;
	rep(i, 1, c.siz) label[i] = (i <= n || i > c.siz - n), fa[i] = i, G[i].clear();
	g = a.E; for(auto v : b.E) g.eb(get<0>(v), get<1>(v) + a.siz, get<2>(v) + a.siz);
	rep(i, 1, n) g.eb(t[i], a.siz - n + i, a.siz + i); sort(g.begin(), g.end());
	for(auto t : g) {
		int w, x, y, fx, fy; tie(w, x, y) = t; fx = gf(x), fy = gf(y); 
		if(fx == fy) continue; fa[fx] = fy; G[x].eb(y, w); G[y].eb(x, w);
	}
	dfs(1, 0); int cnt = 0; rep(i, 1, c.siz) if(label[i]) id[i] = ++cnt;
	g.clear(); tres = 0; vdfs(1, 0, 0, 0); c.siz = cnt; c.E = g; c.res = c.res + tres; 
	return c;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	gen(); pre[1] = MST(b[1]); suf[m] = MST(b[m]);
	rep(i, 2, m) pre[i] = merge(pre[i - 1], MST(b[i]), a[i - 1]);
	per(i, m - 1, 1) suf[i] = merge(MST(b[i]), suf[i + 1], a[i]);
	int Q; scanf("%d", &Q);
	while(Q--) {
		int l, r; scanf("%d %d", &l, &r);
		MST v = merge(suf[r + 1], pre[l - 1], a[m]);
		printf("%lld\n", v.getans());
	}
	return 0;
}
