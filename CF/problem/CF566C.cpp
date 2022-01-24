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

int n, siz[N], son[N], w[N], rt, pos = 1;
bool vis[N];
db res[N], tot, ans = 1e20;
veg G[N];

void gsz(int x, int p) {
	siz[x] = 1; son[x] = 0;
	for(auto v : G[x])
		if(!vis[v.fi] && v.fi ^ p) gsz(v.fi, x), siz[x] += siz[v.fi], chkmax(son[x], siz[v.fi]);
}

void grt(int x, int p, int tot) {
	chkmax(son[x], tot - siz[x]);
	for(auto v : G[x]) if(!vis[v.fi] && v.fi ^ p) grt(v.fi, x, tot);
	if(rt == 0 || son[x] < son[rt]) rt = x;
}

void dfs(int x, int p, ll d, int fro) {
	res[fro] += pow(d, 0.5) * w[x]; tot += pow(d, 1.5) * w[x];
	for(auto v : G[x])
		if(v.fi ^ p) dfs(v.fi, x, v.se + d, fro);
}

void divide(int x) {
	gsz(x, 0); rt = 0; grt(x, 0, siz[x]); x = rt; vis[x] = true;
	db tres = 0; tot = 0;
	for(auto v : G[x]) res[v.fi] = 0, dfs(v.fi, x, v.se, v.fi), tres += res[v.fi];
	//	cerr << x << " " << tot << endl;
	if(tot < ans) ans = tot, pos = x;
	for(auto v : G[x]) if(!vis[v.fi]) {
		int y, w; tie(y, w) = v;
		if(res[y] * 2 < tres) continue;
		divide(y); break;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) w[i] = in;
	rep(i, 2, n) { int u = in, v = in, w = in; G[u].eb(v, w), G[v].eb(u, w); }
	divide(1); printf("%d %.7lf\n", pos, ans);
	return 0;
}
