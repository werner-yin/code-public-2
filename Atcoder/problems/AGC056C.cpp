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

int n, m, dis[N];
veg G[N];
bool vis[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 1, m) {
		int l = in, r = in;
		G[l - 1].eb(r, 0), G[r].eb(l - 1, 0);
	}
	rep(i, 0, n - 1) {
		G[i].eb(i + 1, 1), G[i + 1].eb(i, 1);
	}
	deque < int > q; q.push_back(0); rep(i, 1, n) dis[i] = 1e9;
	while(q.size()) {
		int x = q.front(); q.pop_front(); if(vis[x]) continue; vis[x] = true;
		for(auto v : G[x]) if(dis[v.fi] > dis[x] + v.se) dis[v.fi] = dis[x] + v.se, (v.se ? q.push_back(v.fi) : q.push_front(v.fi));
	}
	rep(i, 0, n - 1) if(dis[i] > dis[i + 1]) putchar('1'); else putchar('0');
	return 0;
}
