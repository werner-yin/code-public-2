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

int n, m, dep[N];
vec G[N];
bool vis[N];
veg ed1, ed2;

void dfs(int x, int p) {
	dep[x] = dep[p] + 1;
	for(auto y : G[x]) if(!dep[y]) dfs(y, x), ed1.eb(x, y); 
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 1, m) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	dfs(1, 0);
	queue < int > q;
	q.ep(1);vis[1] = true;
	while(q.size()) {
		int x = q.front();
		q.pop(); vis[x] = true;
		for(auto y : G[x])
			if(!vis[y]) q.ep(y), vis[y] = true, ed2.eb(x, y);
	}
	for(auto v : ed1) cout << v.fi << " " << v.se << endl;
	for(auto v : ed2) cout << v.fi << " " << v.se << endl;
	return 0;
}
