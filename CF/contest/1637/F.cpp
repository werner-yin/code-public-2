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

int n, h[N];
vec G[N];
ll ans;

int dfs(int x, int p) {
	int mx = 0, mxx = 0;
	for(auto y : G[x]) if(y ^ p) {
			int t = dfs(y, x);
			if(t > mx) mxx = mx, mx = t;
			else chkmax(mxx, t);
	}
	if(p == 0) return ans += max(0, h[x] - mx) + max(0, h[x] - mxx), h[x];
	else {
		int delta = max(0, h[x] - mx);
		ans += delta; return mx + delta;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) h[i] = in;
	rep(i, 2, n) { int u = in, v = in; G[u].eb(v); G[v].eb(u); }
	int rt = 0; rep(i, 1, n) if(h[i] > h[rt]) rt = i;
	dfs(rt, 0); printf("%lld\n", ans);
	return 0;
}
