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

int a[N], n, w[N], fa[N];
ll siz[N], tot[N];
vec G[N];

int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }
void dfs(int x, int p) { tot[x] = w[x]; siz[x] = 1; fa[x] = x; for(auto y : G[x]) dfs(y, x); }

struct node {
	ll siz, tot; int id;
};
bool operator < (node a, node b) { return a.siz * b.tot < b.siz * a.tot; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in, G[a[i]].eb(i); rep(i, 1, n) w[i] = in;
	dfs(0, 0); rep(i, 1, n) if(siz[i] != 1) return puts("-1"), 0; priority_queue < node > q;
	rep(i, 1, n) q.ep((node){ 1, w[i], i });
	ll ans = 0;
	while(q.size()) {
		auto v = q.top(); q.pop();
		int x = v.id; if(v.siz != siz[x]) continue;
		int p = gf(a[x]); fa[x] = p; ans += siz[p] * tot[x]; siz[p] += siz[x]; tot[p] += tot[x];
		if(p) q.ep((node) { siz[p], tot[p], p });
	} printf("%lld\n", ans); return 0;
}
