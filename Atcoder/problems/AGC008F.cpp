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

int n, a[N], f[N], g[N], h[N], t[N], fa[N], high[N], low[N];
vec G[N];

void dfs(int x, int p) {
	fa[x] = p;
	for(auto y : G[x]) if(y ^ p) dfs(y, x), chkmax(f[x], f[y] + 1);
}

int stk[N], top, pre[N], suf[N];

void rdfs(int x, int p) {
	top = 0; for(auto y : G[x]) stk[++top] = y;
	pre[0] = suf[top + 1] = 0;
	rep(i, 1, top) pre[i] = max(pre[i - 1], f[stk[i]] + 1);
	per(i, top, 1) suf[i] = max(suf[i + 1], f[stk[i]] + 1);
	high[x] = max(f[x] - 1, g[x]);
	//cerr << x << " " << f[x] << " " << g[x] << endl;
	rep(i, 1, top)
		if(stk[i] ^ p) g[stk[i]] = max({ pre[i - 1], suf[i + 1] }), chkmin(high[x], g[stk[i]] + 1);
		else chkmin(high[x], max(pre[i - 1], suf[i + 1]) + 1);
	int lfx = f[x]; for(auto y : G[x]) if(y ^ p) f[x] = g[y], rdfs(y, x); f[x] = lfx;
}

const int inf = 0x3f3f3f3f;

void tdfs(int x, int p) {
	h[x] = inf; if(a[x]) h[x] = 0;
	for(auto y : G[x]) if(y ^ p) {
			tdfs(y, x);
			if(h[y] < inf) chkmin(h[x], f[y] + 1);
		}
}

void rtdfs(int x, int p) {
	top = 0; for(auto y : G[x]) stk[++top] = y;
	pre[0] = suf[top + 1] = inf;
	rep(i, 1, top) pre[i] = min(pre[i - 1], (h[stk[i]] < inf ? f[stk[i]] + 1 : inf));
	per(i, top, 1) suf[i] = min(suf[i + 1], (h[stk[i]] < inf ? f[stk[i]] + 1 : inf));
	low[x] = pre[top]; if(a[x]) low[x] = 0;
	rep(i, 1, top) if(stk[i] ^ p) t[stk[i]] = min({ pre[i - 1], suf[i + 1], (a[x] ? 0 : inf)});
	for(auto y : G[x]) if(y ^ p) h[x] = t[y], f[x] = g[y], rtdfs(y, x);
}

char s[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	scanf("%s", s + 1); rep(i, 1, n) a[i] = s[i] - '0';
	dfs(1, 0); g[0] = -1; rdfs(1, 0); tdfs(1, 0); t[1] = inf; rtdfs(1, 0);
	//rep(i, 1, n) cerr << high[i] << " " << low[i] << endl;
	ll ans = 0;
	rep(i, 1, n) {
		if(a[i]) ans += high[i] + 1;
		else ans += max(high[i] - low[i] + 1, 0);
	} ans++; cout << ans << endl;
	return 0;
}
