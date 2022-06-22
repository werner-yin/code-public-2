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

int val[N], ban[N], n;
vec G[N];

void dfs(int x, int p) {
	int ret = 0;
	for(auto y : G[x]) if(y ^ p) {
			dfs(y, x);
			ret |= ban[x] & ban[y];
			ban[x] |= ban[y];
		}
	int t = ret ? 32 - __builtin_clz(ret) : 0;
	val[x] = __builtin_ctz((ban[x] | ((1 << t) - 1)) + 1);
	ban[x] = (ban[x] >> val[x] << val[x]) | (1 << val[x]);
	//cerr << x << " " << val[x] << " " << ban[x] << endl;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	dfs(1, 0); int ans = 0; rep(i, 1, n) chkmax(ans, val[i]); cout << ans << endl;
	return 0;
}
