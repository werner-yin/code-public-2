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

const int N = 110 + 10;

int a[N], b[N], s[N], n;
ll f[2][N * N * 2];

ll calc(ll sa, ll a, ll sb, ll b) {
	return sa * a + sb * b;
}

void solve() {
	n = in;
	rep(i, 1, n) a[i] = in;
	rep(i, 1, n) b[i] = in;
	rep(i, 1, n) s[i] = s[i - 1] + a[i] + b[i];
	int o = 0; rep(j, 0, s[n]) f[o][j] = 1e18; f[o][0] = 0;
	rep(i, 1, n) {
		rep(j, 0, s[n]) f[o ^ 1][j] = 1e18;
		rep(j, 0, s[i - 1]) if(f[o][j] < 1e18) {
			chkmin(f[o ^ 1][j + a[i]], f[o][j] + calc(j, a[i], s[i - 1] - j, b[i]));
			chkmin(f[o ^ 1][j + b[i]], f[o][j] + calc(j, b[i], s[i - 1] - j, a[i]));
		} o ^= 1;
	} ll ans = 1e18; rep(j, 0, s[n]) chkmin(ans, f[o][j]);
	ans *= 2; rep(i, 1, n) ans += ll(a[i] * a[i] + b[i] * b[i]) * (n - 1);
	printf("%lld\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
