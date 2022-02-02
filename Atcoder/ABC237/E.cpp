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

int n, h[N], m;
vec G[N];
ll dis[N];
bool vis[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, n) h[i] = in;
	rep(i, 1, m) {
		int u = in, v = in;
		G[u].eb(v); G[v].eb(u);
	}
	memset(dis, 0xcf, sizeof dis);
	dis[1] = 0; queue < int > q; q.ep(1); vis[1] = true;
	while(q.size()) {
		int x = q.front(); q.pop(); vis[x] = false;
		for(auto y : G[x]) {
			int w = h[x] - h[y];
			if(w < 0) w = 2 * w;
			if(dis[y] < dis[x] + w) {
				dis[y] = dis[x] + w;
				if(!vis[y]) q.ep(y), vis[y] = true;
			}
		}
	} ll ans = 0; rep(i, 1, n) chkmax(ans, dis[i]);
	cout << ans << endl;
	return 0;
}
