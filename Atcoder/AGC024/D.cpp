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
using pll = pair < ll, ll >;
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
const ll inf = 1e18;
int n;
vec G[N];
pll ans = { inf, inf };
ll deg[N], cnt[N];
int dep[N], mxd;

void dfs(int x, int p) {
	int dg = 0; dep[x] = dep[p] + 1; chkmax(mxd, dep[x]);
	for(auto y : G[x]) if(y ^ p) dfs(y, x), dg++;
	chkmax(deg[dep[x]], (ll)dg);
}

pll solve(int rt) {
	mxd = 0; rep(i, 1, n << 1) deg[i] = cnt[i] = dep[i] = 0;
	dfs(rt, 0);
	pll ret = { mxd + 1 >> 1, 1 };
	per(i, mxd - 1, 1) ret.se *= deg[i];
	//cerr << rt << " " << ret.fi << " " << ret.se << endl;
	//rep(i, 1, mxd - 1) cerr << deg[i] << " "; cerr << endl;
	return ret;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(i + n - 1), G[i + n - 1].eb(u), G[v].eb(i + n - 1), G[i + n - 1].eb(v); }
	rep(rt, 1, n + n - 1) chkmin(ans, solve(rt)); cout << ans.fi << " " << ans.se << endl;
	return 0;
}
