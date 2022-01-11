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
const int inf = 0x7fffffff;

int mod, C;
ll lim, n;

ll g0[N], g1[N];

ll qp(ll x, int t) { x %= mod; ll res = 1; for(; t; t = t >> 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

namespace calcg {
	const int N = 20;
	int y[N], fac[N], ifac[N], pre[N], suf[N], m;
	void init() {
		m = C + 2;
		fac[0] = 1; rep(i, 1, m) fac[i] = 1ll * fac[i - 1] * i % mod; ifac[m] = qp(fac[m], mod - 2);
		per(i, m - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
		rep(i, 1, m) y[i] = qp(i, C), y[i] = (y[i] + y[i - 1]) % mod;
	}
	int calc(ll v) {
		v %= mod;
		pre[0] = 1; rep(i, 1, m) pre[i] = 1ll * pre[i - 1] * (v - i + mod) % mod;
		suf[m + 1] = 1; per(i, m, 1) suf[i] = 1ll * suf[i + 1] * (v - i + mod) % mod;
		ll res = 0;
		rep(i, 1, m) {
			res += 1ll * pre[i - 1] * suf[i + 1] % mod * ifac[i - 1] % mod * ifac[m - i] % mod * y[i] % mod * (m - i & 1 ? mod - 1 : 1) % mod;
			res %= mod;
		} return res;
	}
}

using calcg :: calc;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = lin, C = in, mod = in, lim = sqrtl(n);
	calcg :: init(); //cerr << lim << endl;
	rep(i, 1, lim) g0[i] = (calc(i) - 1) % mod, g1[i] = (calc(n / i) - 1) % mod;
	rep(i, 2, lim) {
		g0[i] = (g0[i] + mod) % mod; if(g0[i] == g0[i - 1]) continue;
		ll pc = qp(i, C), pg = g0[i - 1];
		int l1 = lim / i, l2 = min(n / i / i, lim); chkmin(l1, l2);
		rep(j, 1, l1) g1[j] = (g1[j] - pc * (g1[j * i] - pg)) % mod;
		ll tt = n / i;
		if(tt < inf) {
			int t = tt;
			rep(j, l1 + 1, l2) g1[j] = (g1[j] - pc * (g0[t / j] - pg)) % mod;
		} else {
			ll t = tt;
			rep(j, l1 + 1, l2) g1[j] = (g1[j] - pc * (g0[t / j] - pg)) % mod;
		}
		ll st = 1ll * i * i;
		per(j, lim, st) g0[j] = (g0[j] - pc * (g0[j / i] - pg)) % mod;
	}
	ll ans = 0;
	rep(i, 1, lim) {
		g1[i] = (g1[i] + mod) % mod;
		ans += 1ll * i * i % mod * g1[i] % mod; ans %= mod;
	} printf("%lld\n", ans);
	return 0;
}
