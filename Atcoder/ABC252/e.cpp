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

int n, m, u[N], v[N], w[N], pre[N];
ll dis[N];
veg G[N];
bool vis[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, m) u[i] = in, v[i] = in, w[i] = in, G[u[i]].eb(v[i], i), G[v[i]].eb(u[i], i);
	memset(dis, 0x3f, sizeof dis);
	priority_queue < pair < ll, int >, vector < pair < ll, int > >, greater < pair < ll, int > > > q;
	q.ep(0, 1); dis[1] = 0;
	while(q.size()) {
		int x = q.top().se; q.pop(); if(vis[x]) continue; vis[x] = true;
		for(auto v : G[x]) {
			int y = v.fi, w = ::w[v.se];
			if(dis[x] + w < dis[y]) {
				dis[y] = dis[x] + w;
				q.ep(dis[y], y); pre[y] = v.se;
			}
		}
	}
	//rep(i, 1, n) cerr << dis[i] << " "; cerr << endl;
	rep(i, 2, n) printf("%d ", pre[i]); puts("");
	return 0;
}
