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
 
int n, siz[N], mn = 1e9, fa[N];
veg G[N];
bool fl = 0, ok[N];
ll ans;
 
void dfs(int x, int p) {
	siz[x] = 1; fa[x] = p;
	for(auto v : G[x]) if(v.fi ^ p) {
			dfs(v.fi, x), siz[x] += siz[v.fi]; 
		}
}

int top, stk[N], pre[N], suf[N], w[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int u = in, v = in, w = in; G[u].eb(v, w), G[v].eb(u, w); }
	dfs(1, 0);
	rep(x, 1, n) for(auto v : G[x]) if(fa[x] != v.fi) ans += 1ll * min(n - siz[v.fi], siz[v.fi]) * v.se * 2;
	rep(x, 1, n) {
		ok[x] = true;
		for(auto v : G[x]) if(v.fi != fa[x]) ok[x] &= n - siz[v.fi] > siz[v.fi];
	}
	rep(x, 1, n) {
		top = 0; for(auto v : G[x]) if(v.fi != fa[x]) stk[++top] = v.fi, w[top] = v.se;
		pre[0] = suf[top + 1] = n - siz[x] >= siz[x];
		rep(i, 1, top) pre[i] = pre[i - 1] | (siz[stk[i]] >= n - siz[stk[i]]);
		per(i, top, 1) suf[i] = suf[i + 1] | (siz[stk[i]] >= n - siz[stk[i]]);
		rep(i, 1, top) if(!pre[i - 1] && !suf[i + 1] && ok[stk[i]]) chkmin(mn, w[i]);
	}
	cerr << mn << endl;
	cout << ans - mn << endl;
	return 0;
}
