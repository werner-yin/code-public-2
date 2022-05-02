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

const int N = 410;
const int mod = 998244353;

ll fac[N], ifac[N], n, m, dp[N][N][N], ans;
veg pot;

ll C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * ifac[y] % mod * ifac[x - y] % mod; }
ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }
void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * i % mod; ifac[l] = qp(fac[l], mod - 2);
	per(i, l - 1, 0) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, m) { int l = in, r = in; pot.eb(l, r); }
	sort(pot.begin(), pot.end()); init(m);
	dp[0][0][0] = 1;
	rep(i, 0, pot.size() - 1) {
		rep(j, 0, n)
			rep(k, 0, m)
			if(dp[i][j][k]) {
				(dp[i + 1][j][k] += dp[i][j][k]) %= mod;
				if(pot[i].fi <= j + 1)
					(dp[i + 1][max(j, pot[i].se)][k + 1] += dp[i][j][k]) %= mod;
			}
	}
	rep(i, 0, m)
		ans = (ans + (mod + C(m, i) - dp[m][n][i]) % mod * qp(C(m, i)) % mod * m % mod * qp(m - i) % mod) % mod;
	cout << ans << endl; return 0;
}
