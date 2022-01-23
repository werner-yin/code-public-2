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

const int N = 20;
const int mod = 998244353;

ll d[N], n, m;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = lin;
	rep(i, 1, n) d[i] = lin;
	ll ans = 0;
	rep(s, 0, (1 << n) - 1) {
		ll v = 0; bool fl = false;
		rep(i, 1, n) if(s >> i - 1 & 1) {
			if(v == 0) { v = d[i]; continue; }
			__int128 t = v; t /= __gcd(v, d[i]);
			t *= d[i]; if(t > m) { fl = true; break; }
			v = t;
		} if(fl) continue;
		ll res = v == 0 ? 1 : m / v; res %= mod;
		rep(i, 1, n) if(!(s >> i - 1 & 1)) res = 1ll * res * ((m / d[i]) % mod) % mod;
		res = res * (__builtin_popcount(s) - 1) % mod;
		res = (res + mod) % mod;
		if(__builtin_popcount(s) + 1 & 1) ans = (ans - res + mod) % mod;
		else ans = (ans + res) % mod;
	} cout << ans << endl;
	return 0;
}
