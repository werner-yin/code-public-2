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

int n, x, y, a[N], K, fa[N], ans;
vec G[N];
bool ned[N], ban[N];

void dfs(int x, int p) {
	fa[x] = p;
	for(auto y : G[x]) if(y ^ p) dfs(y, x);
}

int tdfs(int x, int dep) {
	int tot = ned[x];
	for(auto y : G[x])
		if(y ^ fa[x] && !ban[y]) {
			int ret = tdfs(y, dep + 1);
			if(ret) ans += 2; tot += ret;
		}
	return tot;
}

void solve() {
	n = in, K = in, x = in, y = in; rep(i, 1, K) a[i] = in;
	rep(i, 1, n) G[i].clear(), ned[i] = 0, ban[i] = 0;
	rep(i, 1, K) ned[a[i]] = true;
	rep(i, 2, n) {
		int u = in, v = in;
		G[u].eb(v), G[v].eb(u);
	}
	dfs(y, 0); ans = 0;
	for(; x; x = fa[x], ans++)
		tdfs(x, 0), ban[x] = true;
	printf("%d\n", ans - 1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
