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

int n, mx[N], fa[N], pmx[N], dfn[N], R[N], f[N], g[N], tim;
int tr[N], ans[N];
vec G[N];

void add(int x, int v) { for(; x <= n; x += x & -x) tr[x] += v; }
int query(int x) { int ret = 0; for(; x; x -= x & -x) ret += tr[x]; return ret; }
void clear() { rep(i, 1, n) tr[i] = 0; }

void dfs(int x, int p) {
	fa[x] = p; dfn[x] = ++tim; mx[x] = mx[p], pmx[x] = pmx[p]; if(p > mx[x]) pmx[x] = mx[x], mx[x] = p; else chkmax(pmx[x], p);
	for(auto y : G[x]) if(y ^ p) dfs(y, x); R[x] = tim;
}

vec pot1[N], pot2[N], tpot1[N], tpot2[N];

void tdfs(int x, int p) {
	ans[x] += g[x];
	for(auto y : G[x]) if(y ^ p) ans[y] = ans[x] - f[y], tdfs(y, x);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	dfs(1, 0);
	rep(x, 2, n) for(auto y : G[x]) if(y ^ fa[x]) {
			if(x > mx[x]) pot2[mx[x]].eb(y);
			else pot1[mx[x]].eb(y);
		}
	rep(x, 1, n) tpot1[max(x, mx[x])].eb(x), tpot2[max(x, pmx[x])].eb(x);
	rep(i, 0, n) {
		for(auto v : tpot1[i]) add(dfn[v], 1);
		for(auto v : pot1[i]) /*cerr << "!GET: " << v << endl, */f[v] = query(R[v]) - query(dfn[v] - 1);
	}
	clear();
	rep(i, 0, n) {
		for(auto v : tpot2[i]) /*cerr << "!" << i << " " << v << endl, */add(dfn[v], 1);
		for(auto v : pot2[i]) /*cerr << "!TGET: " << i << " " << v << endl, */f[v] = query(R[v]) - query(dfn[v] - 1);
	}
	rep(x, 2, n) { g[x] = 1; for(auto y : G[x]) if(y ^ fa[x]) g[x] += f[y]; /*cerr << x << " " << f[x] << " " << g[x] << endl;*/ }
	tdfs(1, 0); rep(i, 2, n) printf("%d ", ans[i]); puts("");
	return 0;
}
