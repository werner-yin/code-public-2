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

const int N = 210;

int n, m, lef[N], mat[N], ans[N], mx, cur, vis[N], tim, tp[N], s[N];
vec G[N][N];

bool dfs(int x, int need) {
	if(x < cur) chkmax(mx, x);
	for(auto y : G[x][need]) {
		if(vis[y] == tim) continue; vis[y] = tim;
		if(lef[y]) return lef[y]--, mat[x] = y, tp[x] = need, true;
		rep(i, 1, n) if(mat[i] == y) {
			if(dfs(i, tp[i])) return mat[x] = y, tp[x] = need, true;
		}
	} return false;
}

void solve() {
	n = in, m = in; rep(i, 1, m) lef[i] = in;
	rep(i, 1, n) {
		rep(j, 1, m) G[i][j].clear();
		mat[i] = m + 1; tp[i] = m + 1; 
	}
	rep(i, 1, n) {
		rep(j, 1, m) {
			int x = in; if(!x) continue;
			G[i][x].eb(j);
		}
	} rep(i, 1, n) s[i] = in;
	rep(i, 1, n) {
		ans[i] = i; cur = i; ++tim; 
		rep(j, 1, m) if(G[i][j].size()) {
			mx = 0; if(dfs(i, j)) { if(j <= s[i]) ans[i] = 0; break; }
			if(j <= s[i]) chkmin(ans[i], i - mx);
		}
	} rep(i, 1, n) printf("%d ", tp[i]); puts("");
	rep(i, 1, n) printf("%d ", ans[i]); puts("");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	int T = in; in; while(T--) solve(); return 0;
}
