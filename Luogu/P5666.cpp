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

int n, siz[N], st[K + 1][N], dfn[N], R[N], tim, son[N], tson[N], top, stk[N], fa[N], vson[N], vsiz[N];
ll ans;
vec G[N];

void dfs(int x, int p) {
	dfn[x] = ++tim; son[x] = tson[x] = 0; siz[x] = 1; fa[x] = p;
	for(auto y : G[x])
		if(y ^ p) dfs(y, x), siz[x] += siz[y], son[x] = siz[y] > siz[son[x]] ? y : son[x];
	top = 0; for(auto y : G[x]) if(y ^ p) stk[++top] = y;
	sort(stk + 1, stk + top + 1, [&](auto a, auto b) { return siz[a] > siz[b]; });
	stk[top + 1] = stk[top + 2] = 0; tson[x] = stk[2]; R[x] = tim;
	st[0][x] = son[x]; rep(i, 1, K) st[i][x] = st[i - 1][st[i - 1][x]];
	vsiz[x] = siz[x]; vson[x] = son[x];
}

bool check(int x, int tsiz) { return max(tsiz - vsiz[x], vsiz[vson[x]]) <= tsiz / 2; }

int calcdn(int x, int tsiz) {
	per(i, K, 0) if(st[i][x] && vsiz[st[i][x]] >= tsiz / 2) x = st[i][x];
	return (check(x, tsiz) ? x : 0) + (check(fa[x], tsiz) ? fa[x] : 0) + (check(vson[x], tsiz) ? vson[x] : 0);
}

void vdfs(int x, int p) {
	for(auto y : G[x]) if(y ^ p) {
			vsiz[x] = n - siz[y]; vson[x] = son[x] == y ? tson[x] : son[x];
			if(vsiz[p] > vsiz[vson[x]]) vson[x] = p;
			st[0][x] = vson[x]; rep(i, 1, K) st[i][x] = st[i - 1][st[i - 1][x]];
			ans += calcdn(y, vsiz[y]); ans += calcdn(x, vsiz[x]);
			cerr << calcdn(y, vsiz[y]) << " " << vson[x] << " " << tson[x] << " " << calcdn(x, vsiz[x]) << " " << y << endl;
			vdfs(y, x);
		}
	vsiz[x] = siz[x]; vson[x] = son[x];
	st[0][x] = vson[x]; rep(i, 1, K) st[i][x] = st[i - 1][st[i - 1][x]];
}

void solve() {
	n = in; rep(i, 1, n) G[i].clear(); rep(i, 1, n) rep(j, 0, K) st[j][i] = 0;
	rep(i, 2, n) {
		int u = in, v = in;
		G[u].eb(v); G[v].eb(u);
	}
	tim = ans = 0; dfs(1, 0); vdfs(1, 0);
	printf("%lld\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
