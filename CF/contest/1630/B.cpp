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

int n, K, a[N];
vec G[N];

struct node {
	int seg, st, tl;
} val[N << 2];


node operator + (node a, node b) {
	node c = a; c.st -= b.seg;
	if(c.st >= 0) c.st += b.st, c.tl = 1;
	else c.seg += -c.st, c.st = b.st, c.tl = b.tl;
	return c;
}

void init(int o, int v) {
	if(v == 1) val[o].seg = 1, val[o].st = 0, val[o].tl = 0;
	else val[o].seg = 0, val[o].st = 1, val[o].tl = 1;
}

void build(int o = 1, int l = 1, int r = n) {
	val[o].seg = val[o].st = 0; if(l == r) return init(o, 0); int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); val[o] = val[o << 1] + val[o << 1 | 1];
}

void upd(int pos, int v, int o = 1, int l = 1, int r = n) {
	if(l == r) return init(o, v); int mid = l + r >> 1;
	if(pos <= mid) upd(pos, v, o << 1, l, mid); else upd(pos, v, o << 1 | 1, mid + 1, r);
	val[o] = val[o << 1] + val[o << 1 | 1];
}

void add(int x) {
	for(auto v : G[x]) upd(v, 1);
}

void del(int x) {
	for(auto v : G[x]) upd(v, 0);
}

bool check() {
	return val[1].seg - val[1].st >= K;
}

void output(int x, int y) {
	veg pot; int cur = 0, lst = 0;
	rep(i, 1, n) {
		if(a[i] >= x && a[i] <= y) cur++;
		else cur--;
		if(cur >= 1) assert(cur == 1), pot.eb(lst + 1, i), lst = i, cur = 0;
	}
	if(lst != n) {
		while(cur <= 0) lst = pot.back().fi - 1, pot.pop_back(), cur++;
		pot.eb(lst + 1, n);
	} while(pot.size() > K) {
		auto x = pot.back(); pot.pop_back();
		auto y = pot.back(); pot.pop_back();
		pot.eb(y.fi, x.se);
	} assert(pot.size() == K); for(auto v : pot) printf("%d %d\n", v.fi, v.se), assert(v.fi <= v.se);
}

void solve() {
	n = in, K = in; rep(i, 1, n) a[i] = in, G[i].clear();
	rep(i, 1, n) G[a[i]].eb(i);
	build();
	int r = 0; int al = 0, ar = 0, lena = n + 10;
	rep(l, 1, n) {
		//cerr << l << " " << r << " " << " " << val[1].seg << " " << val[1].st << " " << check() << endl;
		while(r < n && !check()) add(++r);
		//cerr << l << " " << r << " " << check() << endl;
		if(r == n && !check()) break; assert(check());
		if(r - l < lena) lena = r - l, al = l, ar = r;
		del(l);
	} assert(al && ar);
	printf("%d %d\n", al, ar); output(al, ar);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
