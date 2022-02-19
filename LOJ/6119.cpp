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

int tp[N], n;
ll tot[N], s[N];
vec G[N];
bool vis[N];
int siz[N], son[N], RT;
unordered_map < int, int > f, g;

void gsz(int x, int p) {
	son[x] = 0; siz[x] = 1; for(auto y : G[x]) if(y ^ p && !vis[y]) gsz(y, x), siz[x] += siz[y], chkmax(son[x], siz[y]);
}
void grt(int x, int p, int tsiz) {
	chkmax(son[x], tsiz - siz[x]); if(RT == 0 || son[x] < son[RT]) RT = x;
	for(auto y : G[x]) if(y ^ p && !vis[y]) grt(y, x, tsiz);
}
void dfs(int x, int p, int s, unordered_map < int, int > &f) {
	s += tp[x]; f[s]++;
	for(auto y : G[x]) if(y ^ p && !vis[y]) dfs(y, x, s, f);
}
void calc(int x, int p, int s) {
	s += tp[x]; tot[x] += f[-s] - g[-s];
	for(auto y : G[x]) if(y ^ p && !vis[y]) calc(y, x, s);
}

void divide(int x) {
	gsz(x, 0); RT = 0; grt(x, 0, siz[x]); x = RT; vis[x] = true;
	f.clear(); dfs(x, 0, 0, f); tot[x] = tot[x] + f[0];
	for(auto y : G[x]) if(!vis[y]) {
			g.clear(); dfs(y, x, tp[x], g);
			calc(y, x, 0);
		}
	for(auto y : G[x]) if(!vis[y]) divide(y);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) tp[i] = in ? 1 : -1;
	rep(i, 2, n) { int u = in, v = in; G[u].eb(v); G[v].eb(u); }
	divide(1); rep(i, 1, n) s[i] = s[i - 1] + tot[i];
	int pos = 1; ll vtot = s[n]; 
	ll ans = 0;
	rep(i, 1, n) {
		while(2 * (s[i] - s[pos - 1]) > vtot) pos++;
		ans += pos - 1;
	} printf("%lld\n", ans);
	return 0;
}
