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

int fa[21][N], a[N], R, n;
vec G[N];
ll ans;

void dfs(int x, int p) {
	fa[0][x] = p; rep(i, 1, 20) fa[i][x] = fa[i - 1][fa[i - 1][x]];
	ll mn = 1e18;
	rep(i, 0, 20) {
		if(fa[i][x]) chkmin(mn, 1ll * a[fa[i][x]] * (i + 1));
		else chkmin(mn, 1ll * a[R] * (i + 1));
	} mn += a[x]; if(p) ans += mn;
	for(auto y : G[x]) if(y ^ p) dfs(y, x);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in, R = R == 0 || a[R] > a[i] ? i : R;
	rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	dfs(R, 0); printf("%lld\n", ans);
	return 0;
}
