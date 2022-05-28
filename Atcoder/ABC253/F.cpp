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

pii repl[N];
vector < pair < int, ll > > add[N << 2];
int n, m, q;

void build(int o = 1, int l = 1, int r = m) {
	add[o].eb(-1, 0); if(l == r) return; int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
}

void upd(int xl, int xr, int t, ll v, int o = 1, int l = 1, int r = m) {
	if(xl <= l && r <= xr) return add[o].eb(t, add[o].back().se + v), void(); int mid = l + r >> 1;
	if(xl <= mid) upd(xl, xr, t, v, o << 1, l, mid); if(xr > mid) upd(xl, xr, t, v, o << 1 | 1, mid + 1, r);
}

ll query(int p, int lim, int o = 1, int l = 1, int r = m) {
	ll ret = add[o].back().se - add[o][lower_bound(add[o].begin(), add[o].end(), pair < int, ll >(lim, 0)) - add[o].begin() - 1].se; if(l == r) return ret; int mid = l + r >> 1;
	if(p <= mid) return ret + query(p, lim, o << 1, l, mid); else return query(p, lim, o << 1 | 1, mid + 1, r) + ret;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, q = in;
	rep(i, 1, n) repl[i] = { 0, 0 };
	build();
	rep(i, 1, q) {
		int op = in, x = in, y = in, z;
		if(op == 1) {
			z = in; upd(x, y, i, z);
		} else if(op == 2) repl[x] = { i, y };
		else {
			int t = repl[x].fi; ll ans = repl[x].se;// cerr << "!" << repl[x].fi << endl;
			ans += query(y, t); printf("%lld\n", ans);
		}
	}
	return 0;
}
