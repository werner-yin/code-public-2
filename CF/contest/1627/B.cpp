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

int n, a[N], m;

void solve() {
	n = in, m = in;
	int tot = 0;
	rep(i, 1, n) rep(j, 1, m) {
		int t = 0;
		for(auto v : { pii{ 1, 1 }, pii{ 1, m }, pii{ n, 1 }, pii{ n, m } }) {
			chkmax(t, abs(i - v.fi) + abs(j - v.se));
		} a[++tot] = t;
	}
	sort(a + 1, a + tot + 1);
	rep(i, 1, tot) printf("%d ", a[i]);
	puts("");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
