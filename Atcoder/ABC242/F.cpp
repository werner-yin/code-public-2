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

const int N = 2510;
const int mod = 998244353;

ll f[N][N], g[N][N], tf[N][N], tg[N][N];
int n, m, b, w;
ll fac[N], ifac[N];

ll qp(ll x, int t) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * i % mod; ifac[l] = qp(fac[l], mod - 2);
	per(i, l - 1, 0) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}
ll C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * ifac[y] % mod * ifac[x - y] % mod; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, b = in, w = in;
	init(n * m);
	rep(i, 1, n) rep(j, 1, m) {
		f[i][j] = C(i * j, b), g[i][j] = C(i * j, w);
		rep(k, 1, i) rep(d, 1, j)
			if(k != i || j != d)
				f[i][j] = (f[i][j] + mod - C(i, k) * C(j, d) % mod * f[k][d] % mod) % mod,
					g[i][j] = (g[i][j] + mod - C(i, k) * C(j, d) % mod * g[k][d] % mod) % mod;
	}
	ll ans = 0;
	rep(i, 1, n) rep(j, 1, m) rep(k, 1, n) rep(l, 1, m) {
		ans = (ans + f[i][j] * g[k][l] % mod * C(n, i) % mod * C(m, j) % mod *
			   C(n - i, k) % mod * C(m - j, l) % mod) % mod;
	} cout << ans << endl;
	return 0;
}
