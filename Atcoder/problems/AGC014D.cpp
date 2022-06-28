#include <bits/stdc++.h>

#define in read<int>()
#define lin read<ll>()
#define fi first
#define se second
#define eb emplace_back
#define ep emplace
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

template < typename T > void chkmax(T &x, const T &y) { x = x < y ? y : x; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 1e6 + 10;

int n, fa[N], deg[N], dep[N];
vec G[N], T[N];

void dfs(int x, int p) {
	fa[x] = p; dep[x] = dep[p] + 1;
	for(auto y : G[x]) if(y ^ p) {
			T[x].eb(y), deg[x]++, dfs(y, x);
		}
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	if(n == 2) return puts("Second"), 0;
	int rt = 0;
	rep(i, 1, n) if(G[i].size() > 1) rt = i;
	dfs(rt, 0);
	priority_queue < pii > q; rep(i, 1, n) if(T[i].size() == 0) q.ep(dep[i], i);
	while(q.size()) {
		int x = q.top().se; q.pop(); if(!fa[x]) break;
		if(deg[fa[x]] > 1) return puts("First"), 0;
		int z = fa[fa[x]]; if(z && !--deg[z]) q.ep(dep[z], z);
	} puts("Second");
	return 0;
}
