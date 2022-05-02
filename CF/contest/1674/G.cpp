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

int dp[N], n, m, deg[N];
queue < int > q;
vec G[N], R[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, m) { int u = in, v = in; G[u].eb(v), R[v].eb(u); deg[v]++; }
	rep(i, 1, n) if(deg[i] == 0) q.ep(i); int ans = 0;
	while(q.size()) { 
		int x = q.front(); q.pop(); chkmax(dp[x], 1); chkmax(ans, dp[x]);
		for(auto y : G[x]) {
			if(G[x].size() > 1 && R[y].size() > 1) chkmax(dp[y], dp[x] + 1);
			if(!--deg[y]) q.ep(y);
		}
	} cout << ans << endl;
	return 0;
}
