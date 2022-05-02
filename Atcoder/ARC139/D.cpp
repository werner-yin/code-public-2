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

const int N = 2010;
const int mod = 998244353;

int pw[N][N], C[N][N], n, m, K, X, cnt[N], ans;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, K = in, X = in;
	rep(i, 0, K) rep(j, (C[i][0] = 1), i) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	pw[0][0] = 1;
	rep(i, 1, m) rep(j, (pw[i][0] = 1), K) pw[i][j] = 1ll * pw[i][j - 1] * i % mod;
	rep(i, 1, n) cnt[in]++; per(i, m, 1) cnt[i] += cnt[i + 1];
	rep(i, 1, m) {
		int A = cnt[i];
		rep(B, 0, K) {
			if(A <= n - X + 1)
				ans = (ans + 1ll * C[K][B] * pw[i - 1][K - B] % mod * pw[m - i + 1][B] % mod * min(A + B, n - X + 1)) % mod;
			else
				ans = (ans + 1ll * C[K][B] * pw[i - 1][K - B] % mod * pw[m - i + 1][B] % mod * max(A + B - K, n - X + 1)) % mod;
		}
	} printf("%d\n", ans);
	return 0;
}
