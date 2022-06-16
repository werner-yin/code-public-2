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

const int N = 1e6 + 10;

vec G[N];
int n, m, a[N], b[N], fa[20][N], dep[N], add[N], deg[N], tim, dfn[N], R[N], L[N];
bool vis[N];

struct dsu {
	int fa[N], col[N];
	void reset(int n) { rep(i, 1, n) fa[i] = i, col[i] = 0; }
	int gf(int x) {
		if(fa[x] == x) return x;
		int t = gf(fa[x]); col[x] ^= col[fa[x]]; fa[x] = t; return t;
	}
} T, P;

list < pii > pot[N];

int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	per(i, 19, 0) if(dep[fa[i][x]] >= dep[y]) x = fa[i][x];
	if(x == y) return x;
	per(i, 19, 0) if(fa[i][x] != fa[i][y]) x = fa[i][x], y = fa[i][y];
	return fa[0][x];
}

void dfs(int x, int p) {
	dfn[x] = ++tim; fa[0][x] = p; dep[x] = dep[p] + 1; rep(i, 1, 19) fa[i][x] = fa[i - 1][fa[i - 1][x]];
	for(auto y : G[x]) if(y ^ p) dfs(y, x); R[x] = tim;
}

int ans;

void rdfs(int x, int p) {
	for(auto y : G[x]) if(y ^ p) rdfs(y, x), add[x] += add[y], deg[x]++;
	ans += min(2, add[x]); 
}

bool intr(int x, int y) { return dfn[y] >= dfn[x] && dfn[y] <= R[x]; }

int main() {
#ifdef YJR_2333_TEST
	freopen("path.in", "r", stdin); freopen("path.out", "w", stdout);
#endif
	n = in, m = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	dfs(1, 0);
	rep(i, 1, m) {
		a[i] = in, b[i] = in; if(a[i] == b[i]) continue;
		pot[a[i]].eb(b[i], i << 1), pot[b[i]].eb(a[i], i << 1 | 1), add[a[i]] += 1, add[b[i]] += 1, add[L[i] = lca(a[i], b[i])] -= 2;
	}
	rdfs(1, 0); cout << ans << endl; T.reset(m); P.reset(n); int tot = m;
	queue < int > q; rep(i, 1, n) if(deg[i] == 0) q.ep(i);
	while(q.size()) {
		int x = q.front(); q.pop(); deg[fa[0][x]]--; if(fa[0][x] && deg[fa[0][x]] == 0) q.ep(fa[0][x]); vis[x] = true; P.fa[x] = fa[0][x];
		function < pii(void) > getone = [&]() {
			if(!pot[x].size()) return pii{ -1, -1 };
			auto a = *pot[x].rbegin(); pot[x].erase(--pot[x].end());
			if(T.gf(a.se >> 1) != a.se >> 1) return getone();
			if(intr(x, L[a.se >> 1])) return getone();
			return a;
		};
		auto a = getone(), b = getone();
		if(a.fi != -1 && b.fi != -1) {
#ifdef YJR_2333_TEST
			cerr << x << " " << a.fi << " " << a.se << " " << b.fi << " " << b.se << endl;
#endif
			//assert(!vis[a.fi]); assert(!vis[b.fi]);
			++tot; ::L[tot] = lca(a.fi, b.fi), T.fa[a.se >> 1] = tot, T.col[a.se >> 1] = 1;
			T.fa[b.se >> 1] = tot, T.col[b.se >> 1] = 0, T.fa[tot] = tot, T.col[tot] = 0;
			a.fi = P.gf(a.fi), b.fi = P.gf(b.fi), ::a[tot] = a.fi, ::b[tot] = b.fi;
			//if(::b[a.se] != a.fi) T.col[a.se] ^= 1;
			//if(::b[b.se] != b.fi) T.col[b.se] ^= 1;
			if(a.se & 1) T.col[a.se >> 1] ^= 1;
			if(b.se & 1) T.col[b.se >> 1] ^= 1;
#ifdef YJR_2333_TEST
			cerr << T.col[a.se >> 1] << " " << T.col[b.se >> 1] << endl;
#endif
			if(a.fi != b.fi) pot[a.fi].eb(b.fi, tot << 1), pot[b.fi].eb(a.fi, tot << 1 | 1);
		} else {
			if(a.fi != -1) pot[x].eb(a);
			if(b.fi != -1) pot[x].eb(b);
		}
		pot[fa[0][x]].splice(pot[fa[0][x]].end(), pot[x]);
	}
	rep(i, 1, m) {
		T.gf(i); 
		if(!T.col[i]) printf("%d %d\n", a[i], b[i]);
		else printf("%d %d\n", b[i], a[i]);
	}
	return 0;
}
