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
using pll = pair < ll, ll >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x > y ? x : y; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 1e6 + 10;

int n, K;
veg G[N];
ll tot, mid;
pll f[N][3];

pll trans(pll x) { return pll(x.fi - mid, x.se + 1); }
pll operator + (pll a, pll b) { return pll(a.fi + b.fi, a.se + b.se); }
bool operator < (pll a, pll b) { return a.fi == b.fi ? a.se < b.se : a.fi < b.fi; }
pll operator + (pll a, int x) { return pll(a.fi + x, a.se); }

void dfs(int x, int p) {
	f[x][0] = f[x][1] = { 0, 0 }; f[x][2] = max(pll{ 0, 0 }, pll{ -mid, 1 });
	for(auto v : G[x]) {
		int y, w; tie(y, w) = v; if(y == p) continue;
		dfs(y, x);
		f[x][2] = max(f[x][2] + f[y][0], trans(f[x][1] + f[y][1] + w));
		f[x][1] = max(f[x][1] + f[y][0], f[x][0] + f[y][1] + w);
		f[x][0] = f[x][0] + f[y][0];
	} f[x][0] = max({ f[x][0], trans(f[x][1]), f[x][2] });
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in + 1;
	rep(i, 2, n) {
		int u = in, v = in, w = in; tot += abs(w);
		G[u].eb(v, w); G[v].eb(u, w);
	}
	ll l = -tot, r = tot;
	while(l <= r) {
		mid = l + r >> 1; dfs(1, 0);
		if(f[1][0].se >= K) l = mid + 1;
		else r = mid - 1;
	} mid = r; dfs(1, 0); printf("%lld\n", f[1][0].fi + K * mid); return 0;
}
