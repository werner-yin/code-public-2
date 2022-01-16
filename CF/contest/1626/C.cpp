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
const ll INF = 4e18;

int n, k[N], h[N];
ll f[N];

ll calc(ll l, ll r) { return (r - l + 1) * (r - l + 2) / 2; }

void solve() {
	n = in; rep(i, 1, n) k[i] = in; rep(i, 1, n) h[i] = in;
	rep(i, 0, n) f[i] = INF;
	f[0] = 0;
	rep(i, 1, n) {
		int mn = 2e9;
		per(j, i, 1) {
			chkmin(mn, k[j] - h[j] + 1);
			if(mn > k[j - 1]) chkmin(f[i], f[j - 1] + calc(mn, k[i]));
		}
	} printf("%lld\n", f[n]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
