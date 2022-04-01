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

const int N = 510;

int n, mod, g[N][N << 1], C[N][N], f[N][N], fac[N], ifac[N];

ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

#define g(i, j) (g[i][j + N])

bool vis[N][N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("rabbit.in", "r", stdin); 
#endif
	n = in, mod = 1e9 + 7;
	fac[0] = 1; rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod; ifac[n] = qp(fac[n]);
	per(i, n - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
	f[1][0] = f[1][1] = 1;
	rep(i, 1, n) {
		rep(j, -i, i) {
			if(g(i, j)) {
				rep(y, max(0, j), n - i) if((y - j) % 2 == 0)
					(f[i + y][abs((y - j) / 2 + j)] += 1ll * g(i, j) * fac[i + y] % mod * ifac[y] % mod) %= mod;
			}
		}
		rep(j, 0, i)
			if(f[i][j]) {
				rep(x, 1, n - i)
					(g(i + x, j - x) += 1ll * f[i][j] * ifac[i] % mod * ifac[x] % mod) %= mod;
				rep(x, 0, 0)
					rep(y, 0, n - i - x)
					if(x + y >= j && ((x + y - j) % 2 == 0) && x + y > 0)
						(f[i + x + y][abs((x + y - j) / 2 + j - x)] +=
						 1ll * f[i][j] * fac[i + x + y] % mod * ifac[i] % mod * ifac[x] % mod * ifac[y] % mod) %= mod;
			}
	} printf("%d\n", f[n][0]);
	return 0;
}
