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
int val[N], g[N], t[N], ans[N], n;
map < int, int > f[N];

void merge(int x, int y, int &ans) {
	if(f[x].size() < f[y].size()) swap(f[x], f[y]), swap(g[x], g[y]), swap(t[x], t[y]);
	for(auto v : f[y]) {
		if(f[x].count(v.fi ^ g[y] ^ g[x])) chkmax(ans, f[x][v.fi ^ g[x] ^ g[y]] + t[x] + t[y] + v.se);
		rep(i, 0, 25)
			if(f[x].count(v.fi ^ g[y] ^ g[x] ^ (1 << i)))
				chkmax(ans, f[x][v.fi ^ g[y] ^ g[x] ^ (1 << i)] + t[x] + t[y] + v.se);
		//chkmax(f[x][v.fi ^ g[y] ^ g[x]], v.se + t[y] - t[x]);
	}
	for(auto v : f[y]) chkmax(f[x][v.fi ^ g[y] ^ g[x]], v.se + t[y] - t[x]);
}

void dfs(int x) {
	for(auto y : G[x]) dfs(y), chkmax(ans[x], ans[y]);
	g[x] = 0; f[x][0] = 0;
	cerr << x << " " << ans[x] << endl;
	for(auto y : G[x]) t[y]++, g[y] ^= 1 << val[y], merge(x, y, ans[x]);
	cerr << x << " " << ans[x] << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { G[in].eb(i); char t = getchar(); while(!isalpha(t)) t = getchar(); val[i] = t - 'a'; }
	dfs(1);  rep(i, 1, n) printf("%d ", ans[i]); puts("");
	return 0;
}
