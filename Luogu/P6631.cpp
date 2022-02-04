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

int n;
ll a[N];

void solve() {
	n = in; rep(i, 1, n) a[i] = in;
	ll A = 0, B = 0, C = 0, ans = 0; a[n + 1] = 0;
	rep(i, 1, n) {
		a[i] -= min(a[i], A + B);
		ll na = min(a[i], max(0ll, a[i + 1] - A - C)), nb = a[i] - na;
		A += na; B += nb; ans += na + nb;
		if(A + C > a[i + 1]) {
			ll K = A + C - a[i + 1], na = A - K, nc = C - K;
			if(na < 0) C -= K - A, K = A;
			if(nc < 0) A -= K - C, K = C;
			A -= K; C -= K; ans -= K;
		} swap(B, C);
	} printf("%lld\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
