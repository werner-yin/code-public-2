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

const int N = 1 << 18;
const int mod = 998244353;

ll m;
int n, A[20], C[20];
ll B[20];
ll a[N], b[N], c[N];

ll qp(ll x, ll t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; m = lin;
	rep(i, 1, n) A[i] = in, B[i] = lin + 1, C[i] = (mod - qp(A[i], B[i]));
	int U = 1 << n; U--;
	rep(s, 0, U) {
		a[s] = 1; b[s] = 0;
		rep(i, 1, n) if(s >> i - 1 & 1) a[s] = 1ll * a[s] * C[i] % mod, b[s] += B[i];
	}
	rep(i, 1, n) {
		ll x = qp(A[i]); c[i] = 1;
		rep(j, 1, n) if(i ^ j) c[i] = 1ll * c[i] * (mod + 1 - A[j] * x % mod) % mod;
		c[i] = (c[i] + mod) % mod; c[i] = qp(c[i]);
	} ll ans = 0;
	rep(s, 0, U) if(b[s] <= m) {
		rep(j, 1, n)
			(ans += 1ll * a[s] * c[j] % mod * qp(A[j], m - b[s]) % mod) %= mod;
	} cout << ans << endl;
	return 0;
}
