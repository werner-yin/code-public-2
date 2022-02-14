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

vec G[N];
map < int, int > g[N];
int c[N], n, f[N];
vec pot;

void merge(int x, int y) {
	if(g[x].size() < g[y].size()) swap(g[x], g[y]), swap(f[x], f[y]);
	f[x] += f[y] + g[y][0];
	for(auto v : g[y]) {
		int delta = min(v.se, g[y][0]) - g[y][0];
		pot.eb(v.fi);
		if(g[x].count(v.fi)) g[x][v.fi] = min(g[x][v.fi], g[x][0]) + delta;
		else g[x][v.fi] = g[x][0] + delta;
	}
}

void dfs(int x) {
	for(auto y : G[x]) dfs(y);
	if(c[x]) { g[x][0] = 1; g[x][c[x]] = 0; return; }
	pot.clear(); for(auto y : G[x]) merge(x, y);
	for(auto v : pot) chkmin(g[x][0], g[x][v] + 1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) G[in].eb(i);
	rep(i, 1, n) c[i] = in;
	dfs(1); printf("%d\n", f[1] + g[1][0]);
	return 0;
}
