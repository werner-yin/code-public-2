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
const int K = 20;

int n, siz[N], st[K + 1][N], dfn[N], R[N], tim, son[N], tson[N], top, stk[N], fa[N], tdel[N];
ll ans;
vec G[N];

void dfs(int x, int p) {
	dfn[x] = ++tim; son[x] = tson[x] = 0; siz[x] = 1; fa[x] = p;
	for(auto y : G[x])
		if(y ^ p) dfs(y, x), siz[x] += siz[y], son[x] = siz[y] > siz[son[x]] ? y : son[x];
	R[x] = tim;
}

void rdfs(int x, int p) {
	top = 0; for(auto y : G[x]) if(y ^ p) stk[++top] = y;
	sort(stk + 1, stk + top + 1, [&](auto a, auto b) { return siz[a] > siz[b]; });
	stk[top + 1] = stk[top + 2] = 0; tson[x] = stk[2];
	//	if(x == 1) tdel[x] = 1e9; else tdel[x] = min(tdel[fa[x]], siz[son[fa[x]]] - siz[x]);
	tdel[x] = min(tdel[fa[x]], siz[son[x]] - siz[tson[x]]);
	cerr << x << " " << tdel[x] << " " << endl;
	for(auto y : G[x]) if(y ^ p) rdfs(y, x);
	st[0][x] = son[x]; rep(i, 1, K) st[i][x] = st[i - 1][st[i - 1][x]];
}

bool check(int x, int tsiz) { return max(tsiz - siz[x], son[x]) <= tsiz / 2; }

int calcdn(int x) {
	int tsiz = siz[x];
	per(i, K, 0) if(st[i][x] && siz[st[i][x]] >= tsiz / 2) x = st[i][x];
	return x + (check(fa[x], tsiz) ? fa[x] : 0);
}

bool intr(int x, int y) { return dfn[x] <= dfn[y] && dfn[y] <= R[x]; }

int calcup(int x) {
	int tsiz = n - siz[x], lsiz = siz[x], lx = x, res = 0; x = 1;
	per(i, K, 0) if(st[i][x] && tdel[st[i][x]] >= lsiz) x = st[i][x];
	if(son[x] != lx) x = son[x];
	res += (max(tsiz - siz[x], siz[tson[x]]) <= tsiz / 2 ? x : 0) +
		(max(tsiz - siz[fa[x]], siz[son[fa[x]]] - lsiz) <= tsiz / 2 ? fa[x] : 0);
	int tlx = x; x = tson[x]; 
	per(i, K, 0) if(st[i][x] && siz[st[i][x]] >= tsiz / 2) x = st[i][x];
	res += (max(tsiz - siz[x], siz[son[x]]) <= tsiz / 2 ? x : 0) +
		(fa[x] != tlx && max(tsiz - siz[fa[x]], siz[son[x]]) <= tsiz / 2 ? fa[x] : 0);
	return res;
}

void vdfs(int x, int p) {
	if(x != 1) {
		ans += calcdn(x); ans += calcup(x);
		//		cerr << calcdn(x) << " " << calcup(x) << " " << x << endl;
	}
	for(auto y : G[x]) if(y ^ p) vdfs(y, x);
}

void solve() {
	n = in; rep(i, 1, n) G[i].clear(); rep(i, 1, n) rep(j, 0, K) st[j][i] = 0;
	tdel[0] = 1e9;
	rep(i, 2, n) {
		int u = in, v = in;
		G[u].eb(v); G[v].eb(u);
	}
	tim = ans = 0; dfs(1, 0); rdfs(1, 0); vdfs(1, 0);
	printf("%lld\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
