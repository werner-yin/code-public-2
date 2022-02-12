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

int n, a[N];

void solve() {
	n = in; rep(i, 1, n) a[i] = in;
	ll ans = 0;
	rep(i, 2, n - 1) ans += a[i] + 1 >> 1;
	bool fl1 = 0, fl2 = 0; int ct = 0, ctt = 0;
	rep(i, 2, n - 1) fl1 |= a[i] % 2 == 0, fl2 |= a[i] & 1, ct += a[i] >= 2, ctt += a[i] >= 1;
	if(fl2 && !fl1 && (ct < 2 && (!(ct == 1 && ctt >= 2)))) puts("-1");
	else printf("%lld\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
