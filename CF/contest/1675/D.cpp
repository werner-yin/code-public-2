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

int n, p[N], tot;
vec G[N], pot[N];

void dfs(int x, int id) {
	if(id == 0) ++tot, pot[tot].eb(x), id = tot;
	else pot[id].eb(x);
	for(auto y : G[x])
		dfs(y, id), id = 0;
}

void solve() {
	n = in; rep(i, 1, n) p[i] = in, G[i].clear(), pot[i].clear();
	int rt = 0; tot = 0;
	rep(i, 1, n)
		if(p[i] ^ i)
			G[p[i]].eb(i);
		else rt = i;
	dfs(rt, 0);
	printf("%d\n", tot);
	rep(i, 1, tot) {
		printf("%lu\n", pot[i].size());
		for(auto v : pot[i]) printf("%d ", v);
		puts("");
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
