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
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) >> 1;

int n, m, k, fac[N << 1], ifac[N << 1];

ll qp(ll x, int t) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }
ll C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : 1ll * fac[x] * ifac[y] % mod * ifac[x - y] % mod; }

void init(int n) {
	fac[0] = 1; rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[n] = qp(fac[n], mod - 2); per(i, n - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
}

void solve() {
	n = in, m = in, k = in;
	if(n == m) return printf("%lld\n", 1ll * n * k % mod), void();
	init(n);
	int ans = 0;
	rep(i, 1, m) {
		(ans += 1ll * C(n - i - 1, m - i) * qp(inv2, n - i) % mod * i % mod) %= mod;
	} ans = 1ll * ans * k % mod; printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
