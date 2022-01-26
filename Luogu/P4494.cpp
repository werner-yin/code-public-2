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
const int mod = 1e9 + 7;

int n, m;
int u[N], v[N], c[N], cur[N], pw[N], dep[N];
bool vis[N], ban[N];
vec G[N];
char s[N];

namespace sub1 {
	int tot;
	void dfs(int x, int p) {
		vis[x] = true; cur[x] = c[x];
		for(auto y : G[x])
			if(y ^ p && !ban[y]) {
				if(!vis[y]) dfs(y, x), cur[x] ^= cur[y];
				else tot++;
			}
	}
	void calc() {
		tot = 0; bool fl = false;
		rep(i, 1, n) vis[i] = 0;
		rep(i, 1, n) if(!vis[i] && !ban[i]) dfs(i, 0), fl |= cur[i];
		if(fl) printf("%d ", 0);
		else printf("%d ", pw[tot / 2]);
	}
	void solve() {
		calc(); rep(i, 1, n) ban[i] = true, calc(), ban[i] = false;
		puts("");
	}
}

namespace sub2 {
	int tot, ans[N], mnd[N], cnt, anc[N];
	void dfs(int x, int p) {
		dep[x] = dep[p] + 1; cur[x] = c[x]; mnd[x] = dep[x];
		for(auto y : G[x])
			if(y ^ p) {
				if(!dep[y]) dfs(y, x), cur[x] ^= cur[y], chkmin(mnd[x], mnd[y]);
				else if(dep[y] < dep[x]) tot++, chkmin(mnd[x], dep[y]);
			}
	}
	void tdfs(int x, int p, int ac) {
		anc[x] = ac;
		int ctot = tot, ccnt = cnt - cur[ac], fl = 0, curcolor = cur[ac] ^ cur[x];
		for(auto y : G[x])
			if(y ^ p) {
				if(dep[y] == dep[x] + 1) {
					if(mnd[y] < dep[x]) ctot--, curcolor ^= cur[y];
					else if(cur[y]) fl = true;
				} else ctot--;
			}
		ccnt += curcolor;
		if(fl || ccnt) ans[x] = 0; else ans[x] = pw[ctot];
		for(auto y : G[x]) if(dep[y] == dep[x] + 1) tdfs(y, x, ac);
	}
	void solve() {
		tot = cnt = 0; rep(i, 1, n) dep[i] = ans[i] = anc[i] = 0;
		rep(i, 1, n) if(!dep[i]) dfs(i, 0), cnt += cur[i]; ans[0] = cnt ? 0 : pw[tot];
		rep(i, 1, n) if(!anc[i]) tdfs(i, 0, i); rep(i, 0, n) printf("%d ", ans[i]); puts("");
	}
}

void solve() {
	n = in, m = in; rep(i, 1, n) G[i].clear();
	rep(i, 1, m) u[i] = in, v[i] = in, G[u[i]].eb(v[i]), G[v[i]].eb(u[i]);
	pw[0] = 1; rep(i, 1, m) pw[i] = pw[i - 1] * 2ll % mod;
	scanf("%s", s + 1); rep(i, 1, n) c[i] = s[i] - '0';
	if(n <= 2000) sub1 :: solve();
	else sub2 :: solve();
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
