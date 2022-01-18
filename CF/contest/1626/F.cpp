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

const int N = 1e7 + 10;
const int M = 12252240;
const int mod = 998244353;

int f[M], a[N], n, K, TM;
ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; a[0] = in; int x = in, y = in; K = in, TM = in;
	rep(i, 1, n - 1) 
		a[i] = (1ll * a[i - 1] * x % TM + y) % TM;
	int ans = 0;
	int p1 = qp(n), p2 = 1ll * p1 * (n - 1) % mod, p3 = 1ll * p1 * K % mod;
	rep(i, 0, n - 1) {
		int lef = a[i] % M;
		ans = (ans + 1ll * (a[i] - lef) * p3 % mod) % mod;
		f[lef]++;
	}
	rep(_, 1, K) {
		rep(i, 0, M - 1) if(f[i]) {
			ans = (ans + 1ll * f[i] * p1 % mod * i % mod) % mod;
			int lst = f[i]; f[i] = 1ll * f[i] * p2 % mod;
			int v = i - i % _;
			f[v] = (f[v] + 1ll * lst * p1 % mod) % mod;
		}
	} printf("%lld\n", ans * qp(n, K) % mod);
	return 0;
}
