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

const int N = 110;
const int mod = 1e6 + 3;

int n, mat[N][N], deg[N], fa[N], fac[200010], indeg[N];

int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }

int gauss() {
	int ans = 1; 
	rep(i, 2, n) {
		int p = i; rep(j, i, n) if(mat[j][i]) { p = j; break; }
		if(p ^ i) swap(mat[i], mat[p]), ans = mod - ans; if(!mat[i][i]) continue; 
		rep(j, i + 1, n) if(i ^ j) {
			while(mat[j][i]) {
				ll v = mat[j][i] / mat[i][i];
				rep(t, i, n) mat[j][t] = (mat[j][t] - v * mat[i][t] % mod + mod) % mod;
				if(mat[j][i]) {
					ans = mod - ans;
					rep(t, i, n) swap(mat[i][t], mat[j][t]);
				}
			}
		}
	}
	rep(i, 2, n) if(indeg[i]) ans = 1ll * ans * mat[i][i] % mod; return ans; 
}

void solve() {
	n = in; rep(i, 1, n) { fa[i] = i, deg[i] = 0, indeg[i] = 0; rep(j, 1, n) mat[i][j] = 0; }
	rep(i, 1, n) {
		int s = in, x;
		while(s--) x = in, deg[i]++, indeg[x]++, mat[i][i]++, mat[i][x]--, fa[gf(x)] = gf(i);
	}
	if(n == 1) return puts("1"), void();
	rep(i, 1, n) if(gf(i) != gf(1) || indeg[i] != deg[i]) if(deg[i] || indeg[i]) return puts("0"), void();
	rep(i, 1, n) rep(j, 1, n) mat[i][j] = (mat[i][j] + mod) % mod;
	int ans = 1ll * gauss() * max(1, deg[1]) % mod; rep(i, 1, n) if(deg[i]) ans = 1ll * ans * fac[deg[i] - 1] % mod; printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	fac[0] = 1; rep(i, 1, 200000) fac[i] = 1ll * fac[i - 1] * i % mod;
	int T = in; while(T--) solve(); return 0;
}
