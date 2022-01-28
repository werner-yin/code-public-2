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

int n, m, a[N], b[N];
ll f[N][2];

void solve() {
	n = in, m = in; rep(i, 1, n) a[i] = in;
	int t = 0; rep(i, 1, m) b[i] = in, t = __gcd(t, b[i]);
	rep(i, 0, t - 1) f[i][0] = 0, f[i][1] = -1e18;
	rep(i, 1, n) {
		int p = (i - 1) % t;
		ll f0 = max(f[p][0] + a[i], f[p][1] - a[i]);
		ll f1 = max(f[p][0] - a[i], f[p][1] + a[i]);
		f[p][0] = f0; f[p][1] = f1;
	} ll f0 = 0, f1 = 0;
	rep(i, 0, t - 1) f0 += f[i][0], f1 += f[i][1];
	printf("%lld\n", max(f0, f1));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
