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

const int N = 3e5 + 10;
const ll INF = 1e18;

int n, c[N], f[N], g[N], h[N], fa[N], siz[N], tot, ans[N];
vec G[N];

void dfs(int x, int p) {
	fa[x] = p; siz[x] = c[x]; fa[x] = p; f[x] = h[x] = c[x];
	for(auto y : G[x]) if(y ^ p) {
			dfs(y, x); siz[x] += siz[y]; h[x] |= c[y]; f[x] |= c[y];
			if(siz[y] >= 2) f[x] |= f[y];
		}
	h[x] |= c[p]; //f[x] |= h[x];
	//cerr << x << " " << f[x] << " " << siz[x] << " " << h[x] << endl;
}

int stk[N], top, pcan[N], scan[N];

void rdfs(int x, int p) {
	ans[x] = f[x] | g[x] | h[x] | c[x];
	//cerr << x << " " << g[x] << " " << ans[x] << endl;
	g[x] |= c[x];
	top = 0; for(auto y : G[x]) if(y ^ p) stk[++top] = y;
	pcan[0] = scan[top + 1] = 0;
	rep(i, 1, top) pcan[i] = pcan[i - 1] | (siz[stk[i]] >= 2 && f[stk[i]]) | c[stk[i]];
	per(i, top, 1) scan[i] = scan[i + 1] | (siz[stk[i]] >= 2 && f[stk[i]]) | c[stk[i]];
	rep(i, 1, top) g[stk[i]] = (tot - siz[stk[i]] >= 2 && (pcan[i - 1] | scan[i + 1] | g[x])) || c[x];
	for(auto y : G[x]) if(y ^ p) rdfs(y, x);
}

void solve() {
	n = in; tot = 0; rep(i, 1, n) c[i] = in, tot += c[i], f[i] = g[i] = h[i] = ans[i] = 0;
	rep(i, 1, n) G[i].clear();
	rep(i, 2, n) {
		int u = in, v = in;
		G[u].eb(v); G[v].eb(u);
	}
	//cerr << x << " " << g[x] << " " << ans[x] << endl;
	g[x] |= c[x];
	top = 0; for(auto y : G[x]) if(y ^ p) stk[++top] = y;
	pcan[0] = scan[top + 1] = 0;
	rep(i, 1, top) pcan[i] = pcan[i - 1] | (siz[stk[i]] >= 2 && f[stk[i]]) | c[stk[i]];
	per(i, top, 1) scan[i] = scan[i + 1] | (siz[stk[i]] >= 2 && f[stk[i]]) | c[stk[i]];
	rep(i, 1, top) g[stk[i]] = (tot - siz[stk[i]] >= 2 && (pcan[i - 1] | scan[i + 1] | g[x])) || c[x];
	for(auto y : G[x]) if(y ^ p) rdfs(y, x);
}

void solve() {
	n = in; tot = 0; rep(i, 1, n) c[i] = in, tot += c[i], f[i] = g[i] = h[i] = ans[i] = 0;
	rep(i, 1, n) G[i].clear();
	rep(i, 2, n) {
		int u = in, v = in;
	dfs(1, 0); rdfs(1, 0); rep(i, 1, n) printf("%d ", ans[i]);
	puts("");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = 1; T; T--) solve();
	return 0;
}
