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

queue < int > q;
int n, tdis[N], ans[N], siz[N], fa[N], dep[N], res[N], rt, son[N];
vec G[N];
bool vis[N];

void gsz(int x, int p) {
	siz[x] = 1, son[x] = 0;
	for(auto y : G[x])
		if(y ^ p && !vis[y]) gsz(y, x), siz[x] += siz[y], chkmax(son[x], siz[y]);
}

void grt(int x, int p, int tsiz) {
	chkmax(son[x], tsiz - siz[x]); if(!rt || son[x] < son[rt]) rt = x;
	for(auto y : G[x]) if(y ^ p && !vis[y]) grt(y, x, tsiz);
}

veg pot;

void dfs(int x, int p) {
	if(tdis[x] - dep[x] >= 0) pot.eb(tdis[x] - dep[x], tdis[x]); 
	for(auto y : G[x]) if(y ^ p && !vis[y]) dep[y] = dep[x] + 1, dfs(y, x);
}

int get(int x) {
	auto it = lower_bound(pot.begin(), pot.end(), pii(x + 1, -114));
	if(it == pot.end()) return 0;
	return it->se;
}

void getans(int x, int p) {
	chkmax(ans[x], get(dep[x]));
	for(auto y : G[x]) if(y ^ p && !vis[y]) getans(y, x);
}

void divide(int x) {
	gsz(x, 0), rt = 0; int tsiz = siz[x]; grt(x, 0, siz[x]); x = rt, vis[x] = true; dep[x] = 0; pot.clear(); dfs(x, 0);
	sort(pot.begin(), pot.end()); per(i, int(pot.size()) - 2, 0) chkmax(pot[i].se, pot[i + 1].se); getans(x, 0);
	for(auto y : G[x]) if(!vis[y]) divide(y);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int a = in, b = in; G[a].eb(b), G[b].eb(a); }
	memset(tdis, 0x3f, sizeof tdis); int K = in; rep(i, 1, K) { int x = in; tdis[x] = 0, q.ep(x); }
	while(q.size()) {
		int x = q.front(); q.pop();
		for(auto y : G[x])
			if(tdis[y] > tdis[x] + 1)
				tdis[y] = tdis[x] + 1, q.ep(y);
	} divide(1); rep(i, 1, n) printf("%d ", ans[i]); puts("");
	return 0;
}
