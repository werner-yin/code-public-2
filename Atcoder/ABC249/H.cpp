#include <bits/stdc++.h>

#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = 2e3 + 10;
const int mod = 998244353;

int a[N], n, C[N][N], pw[N], ipw[N], P[N][N], g[N], b[N], invn;
int ans;

int upd(const int &x) { return x + (x >> 31 & mod); }
ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	invn = qp(n = in); rep(i, 1, n) a[i] = in, ++b[a[i]]; 
	rep(i, 0, n) {
		C[i][0] = 1;
		rep(j, 1, i)
			C[i][j] = upd(C[i - 1][j] + C[i - 1][j - 1] - mod);
	}
	pw[0] = 1; rep(i, 1, n) pw[i] = upd(pw[i - 1] + pw[i - 1] - mod); ipw[n] = qp(pw[n]);
	per(i, n - 1, 0) ipw[i] = upd(ipw[i + 1] + ipw[i + 1] - mod);
	rep(i, 0, n - 1) {
		rep(j, 0, i) {
			P[i][i - j + 1] = upd(P[i][i - j + 1] + 1ll * C[i][j] * upd(1ll * (n - i) * ipw[i + 1] % mod + 1ll * j * ipw[i] % mod - mod) % mod * invn % mod - mod);
			P[i][i - j] = upd(P[i][i - j] + 1ll * C[i][j] * upd(upd(-1ll * (n - i) * ipw[i + 1] % mod) + 1ll * (n - j) * ipw[i] % mod - mod) % mod * invn % mod - mod);
		} P[i][i] = upd(P[i][i] - 1);
	}
	rep(i, 1, n) {
		g[i] = upd(-invn);
		rep(j, 0, i - 1) g[i] = upd(g[i] - 1ll * g[j] * P[i - 1][j] % mod);
		g[i] = 1ll * g[i] * qp(P[i - 1][i]) % mod;
	} rep(i, 1, n) ans = upd(ans + g[b[i]] - mod); ans = upd(ans - g[n]); ans = upd(ans - 1ll * g[0] * (n - 1) % mod);
	cout << ans << endl; return 0;
}
