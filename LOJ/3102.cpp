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

const int N = 5e3 + 10;
const int mod = 998244353;

int f[N][N][3], sum, K, m, siz[N], tf[N], g[N];
ll fac[N], ifac[N], ans[N];
vec G[N];

ll qp(ll x, int t) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

ll C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * ifac[y] % mod * ifac[x - y] % mod; }

void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * i % mod; ifac[l] = qp(fac[l], mod - 2);
	per(i, l - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
}

int tmp[N][3];

void dfs(int x, int p) {
	f[x][0][0] = 1; siz[x] = 1; 
	for(auto y : G[x]) if(y ^ p) {
			dfs(y, x);
			rep(i, 0, siz[x] + siz[y]) tmp[i][0] = tmp[i][1] = tmp[i][2] = 0;
			rep(i, 0, siz[x]) {
				rep(j, 0, siz[y]) {
					(tmp[i + j + 1][0] += 1ll * f[x][i][0] * f[y][j][0] % mod) %= mod;
					(tmp[i + j][1] += 1ll * f[x][i][0] * f[y][j][0] % mod) %= mod;
					
					(tmp[i + j + 1][0] += 2ll * f[x][i][0] * f[y][j][1] % mod) %= mod;
					(tmp[i + j][1] += 1ll * f[x][i][0] * f[y][j][1] % mod) %= mod;
					
					(tmp[i + j][0] += 1ll * f[x][i][0] * f[y][j][2] % mod) %= mod;
					
					(tmp[i + j + 1][1] += 1ll * f[x][i][1] * f[y][j][0] % mod) %= mod;
					(tmp[i + j + 1][2] += 2ll * f[x][i][1] * f[y][j][0] % mod) %= mod;
					
					(tmp[i + j + 1][1] += 2ll * f[x][i][1] * f[y][j][1] % mod) %= mod;
					(tmp[i + j + 1][2] += 2ll * f[x][i][1] * f[y][j][1] % mod) %= mod;
					
					(tmp[i + j][1] += 1ll * f[x][i][1] * f[y][j][2] % mod) %= mod;
					
					(tmp[i + j + 1][0] += 1ll * f[x][i][2] * f[y][j][0] % mod) %= mod;
					(tmp[i + j + 1][0] += 2ll * f[x][i][2] * f[y][j][1] % mod) %= mod;
					(tmp[i + j][0] += 1ll * f[x][i][2] * f[y][j][2] % mod) %= mod;
				}
			}
			siz[x] += siz[y];
			rep(i, 0, siz[x]) rep(j, 0, 2) f[x][i][j] = tmp[i][j];
		}
}

void solve(int tp) {
	K = in; sum += K;
	rep(i, 1, K) { rep(j, 0, K) f[i][j][0] = f[i][j][1] = f[i][j][2] = 0; G[i].clear(); }
	rep(i, 2, K) { int u = in, v = in; G[u].eb(v), G[v].eb(u); } dfs(1, 0);
	rep(i, 1, K) tf[i] = (f[1][i - 1][0] + f[1][i][1] * 2ll + f[1][i][2]) % mod;
	rep(i, 0, K) g[i] = 0;
	if(!tp) rep(i, 1, K) rep(j, i, K) (g[i] += tf[j] * fac[j] % mod * (j - i & 1 ? mod - 1 : 1) % mod * C(j - 1, i - 1) % mod) %= mod;
	else if(tp) {
		rep(i, 2, K) rep(j, i, K) (g[i - 2] += tf[j] * fac[j - 1] % mod * (j - i & 1 ? mod - 1 : 1) % mod * C(j - 1, i - 1) % mod) %= mod;
		rep(i, 0, K) g[i] = mod - g[i];
		rep(i, 1, K) rep(j, i, K) (g[i - 1] += tf[j] * fac[j - 1] % mod * (j - i & 1 ? mod - 1 : 1) % mod * C(j - 1, i - 1) % mod) %= mod;
	}
	per(i, sum, 0) {
		int res = 0; rep(j, 0, K) (res += g[j] * ans[i - j] % mod) %= mod;
		ans[i] = res;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	init(5000); m = in; rep(i, 1, m) solve(i == 1); ll res = 0; rep(i, 1, sum) res = (res + ans[i] * fac[i] % mod) % mod; printf("%lld\n", res);
	return 0;
}
