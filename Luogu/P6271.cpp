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

int p[N], c[N], f[N], y[N], w, K, n = 1, g[N];

ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	K = in, w = in; rep(i, 1, w) p[i] = in, c[i] = in, n = n * qp(p[i], c[i]) % mod;
	int C = K + 2; rep(i, 1, C) y[i] = (y[i - 1] + qp(i, K)) % mod;
	g[0] = 1;
	auto mul = [&](int k, int b) {
				  per(i, C, 1)
					  g[i] = (1ll * g[i] * b + 1ll * g[i - 1] * k) % mod;
				  g[0] = 1ll * g[0] * b % mod;
			  };
	rep(i, 1, C) {
		rep(j, 1, C) if(i != j) mul(qp(i - j + mod) % mod, 1ll * (mod - j) * qp((i - j + mod) % mod) % mod);
		rep(j, 1, C) f[j] = (f[j] + 1ll * g[j] * y[i] % mod) % mod;
		rep(j, 0, C) g[j] = 0; g[0] = 1;
	} //rep(i, 1, C) cerr << f[i] << " "; cerr << endl;
	int pw = 1, ans = 0; 
	rep(i, 1, C) {
		pw = 1ll * n * pw % mod; int res = 1;
		rep(j, 1, w) res = 1ll * (1 - qp(p[j], K - i + mod - 1) + mod) * res % mod;
		res = 1ll * res * pw % mod * f[i] % mod; ans = (ans + res) % mod;
	} printf("%d\n", ans); return 0;
}
