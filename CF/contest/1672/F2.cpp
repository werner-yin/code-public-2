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

vec pot[N];
int id[N], a[N], n, b[N], p[N];
bool vis[N], instk[N], ok;

void dfs(int x) {
	instk[x] = vis[x] = true;
	for(auto y : pot[x]) {
		if(instk[y]) ok = 0;
		if(!vis[y]) dfs(y);
	} instk[x] = 0;
}

void solve() {
	n = in; rep(i, 1, n) pot[i].clear(); rep(i, 1, n) a[i] = in;
	rep(i, 1, n) b[i] = in, pot[a[i]].eb(b[i]), vis[i] = instk[i] = 0;
	ok = 1; int t = 1; rep(i, 1, n) if(pot[i].size() > pot[t].size()) t = i; vis[t] = true;
	rep(i, 1, n) if(!vis[i]) dfs(i);
	if(ok) puts("AC"); else puts("WA");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
