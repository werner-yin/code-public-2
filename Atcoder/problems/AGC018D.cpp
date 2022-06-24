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

int n, siz[N], mn = 1e9;
veg G[N];
bool fl = 0;
ll ans;

void dfs(int x, int p) {
	siz[x] = 1;
	for(auto v : G[x]) if(v.fi ^ p) {
			dfs(v.fi, x), siz[x] += siz[v.fi]; 
		}
}

void rdfs(int x, int p) {
	for(auto v : G[x]) if(v.fi ^ p) {
			ans += 1ll * min(siz[v.fi], n - siz[v.fi]) * v.se * 2;
			if(siz[v.fi] == n - siz[v.fi]) fl = 1, mn = v.se;
			else if(!fl) chkmin(mn, v.se);
			rdfs(v.fi, x);
		}
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int u = in, v = in, w = in; G[u].eb(v, w), G[v].eb(u, w); }
	dfs(1, 0); rdfs(1, 0); cout << ans - mn << endl;
	return 0;
}
