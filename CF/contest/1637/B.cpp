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

const int N = 210;

int n, a[N], cnt[N];
ll f[N];

void solve() {
	n = in; rep(i, 1, n) a[i] = in;
	ll ans = 0;
	rep(s, 1, n) {
		f[s - 1] = 0;
		rep(i, s, n) {
			f[i] = -1e18;
			rep(j, 0, n + 10) cnt[j] = 0;
			int mex = 0;
			per(j, i, s) {
				if(a[j] <= n + 10) ++cnt[a[j]];
				while(cnt[mex]) mex++;
				chkmax(f[i], f[j - 1] + mex + 1);
			} ans += f[i];
		}
	} printf("%lld\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
