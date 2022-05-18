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

int n, m, low[N], dfn[N], siz[N], tim, scc, bel[N], top, stk[N], deg[N];
vec G[N], T[N];
bool vis[N];

void tarjan(int x) {
	dfn[x] = low[x] = ++tim; vis[x] = true; stk[++top] = x;
	for(auto y : G[x])
		if(!dfn[y])	tarjan(y), chkmin(low[x], low[y]);
		else if(vis[y]) chkmin(low[x], dfn[y]);
	if(dfn[x] == low[x]) {
		++scc; int y;
		do {
			y = stk[top--]; bel[y] = scc; vis[y] = false; siz[scc]++;
		} while(y ^ x);
	}
}

void solve() {
	n = in, m = in; rep(i, 1, n) G[i].clear(), dfn[i] = low[i] = bel[i] = stk[i] = 0, vis[i] = 0, T[i].clear(), deg[i] = siz[i] = 0;
	rep(i, 1, m) { int u = in, v = in; G[u].eb(v); }
	top = scc = tim = 0; rep(i, 1, n) if(!dfn[i]) tarjan(i);
	rep(x, 1, n)
		for(auto y : G[x])
			if(bel[x] != bel[y])
				T[bel[x]].eb(bel[y]), ++deg[bel[y]];
	queue < int > q; int tot = 0;
	rep(i, 1, scc) if(deg[i] == 0) q.push(i);
	rep(i, 1, scc) if(siz[i] == 2) return puts("NO"), void();
	while(q.size()) {
		if(q.size() > 1) return puts("NO"), void(); int x = q.front(); q.pop(); tot++;
		for(auto y : T[x])
			if(!--deg[y]) q.push(y);
	} puts("YES"); assert(tot == scc);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
