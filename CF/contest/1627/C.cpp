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

int n, u[N], v[N];
int deg[N], ans[N];
veg G[N];
bool vis[N];

void dfs(int x, int p) {
	vis[x] = true;
	for(auto v : G[x]) {
		if(!vis[v.fi]) {
			ans[v.se] = p;
			dfs(v.fi, p ^ 1);
		}
	}
}

void solve() {
	n = in; rep(i, 1, n) deg[i] = 0, G[i].clear(), vis[i] = 0;
	rep(i, 1, n - 1) {
		u[i] = in, v[i] = in; deg[u[i]]++; deg[v[i]]++;
		G[u[i]].eb(v[i], i); G[v[i]].eb(u[i], i); ans[i] = 0;
	}
	rep(i, 1, n) if(deg[i] >= 3) return puts("-1"), void();
	rep(i, 1, n) if(deg[i] == 1) { dfs(i, 2); break; }
	rep(i, 1, n - 1) printf("%d ", ans[i]);
	puts("");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
