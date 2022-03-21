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

const int N = 2e3 + 10;
const int mod = 924844033;

int n, K;
int f[N << 1][N][2], tot, fac[N];
bool stp[N << 1];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in;
	rep(i, 1, K) rep(_, 0, 1) rep(j, i, n) { ++tot; stp[tot] = j == i; j += K - 1; }
	f[0][0][0] = 1; fac[0] = 1; rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod;
	rep(i, 1, tot)
		rep(j, 0, n) {
		f[i][j][0] = (f[i - 1][j][0] + f[i - 1][j][1]) % mod;
		if(j && !stp[i]) f[i][j][1] = f[i - 1][j - 1][0];
	}
	int ans = 0;
	rep(i, 0, n) {
		if(i & 1) ans = (ans + mod - 1ll * fac[n - i] * (f[tot][i][0] + f[tot][i][1]) % mod) % mod;
		else ans = (ans + 1ll * fac[n - i] * (f[tot][i][0] + f[tot][i][1]) % mod) % mod;
	} printf("%d\n", ans);
	return 0;
}
