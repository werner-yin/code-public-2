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

const int N = 1e4 + 10;

int x[N], n, Q;
vec pot[N << 2];
bitset < N > ans, cur;

void ins(int xl, int xr, int v, int o = 1, int l = 1, int r = n) {
	if(xl <= l && r <= xr) return pot[o].eb(v), void(); int mid = l + r >> 1;
	if(xl <= mid) ins(xl, xr, v, o << 1, l, mid); if(xr > mid) ins(xl, xr, v, o << 1 | 1, mid + 1, r);
}

void solve(int o = 1, int l = 1, int r = n) {
	auto lcur = cur; for(auto v : pot[o]) cur |= cur << v;
	if(l == r) return ans |= cur, cur = lcur, void(); int mid = l + r >> 1;
	solve(o << 1, l, mid); solve(o << 1 | 1, mid + 1, r); cur = lcur;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, Q = in;
	rep(i, 1, Q) {
		int l = in, r = in, x = in;
		ins(l, r, x);
	} cur.set(0); solve();
	vec tpot; for(int p = ans._Find_next(0); p < N && p <= n; p = ans._Find_next(p)) tpot.eb(p);
	printf("%ld\n", tpot.size()); for(auto v : tpot) printf("%d ", v); puts("");
	return 0;
}
