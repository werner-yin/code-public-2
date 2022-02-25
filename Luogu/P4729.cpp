#include <bits/stdc++.h>

#define fi first
#define se second
#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using pii = pair < int, int >;
using veg = vector < pii >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = 1e5 + 10;
const int V = 1e5 + 5;
const int inf = 0x3f3f3f3f;

struct node {
	int mx, cnt, l, r;
	node(int _mx = 0, int _cnt = 0, int _l = 0, int _r = 0) : mx(_mx), cnt(_cnt), l(_l), r(_r) { }
} val[N << 2];

node operator + (node a, node b) {
	node c; c.mx = max(a.mx, b.mx);
	c.cnt = (a.mx == c.mx ? a.cnt : 0) + (b.mx == c.mx ? b.cnt : 0) - (a.r == c.mx && b.l == c.mx);
	c.l = a.l; c.r = b.r; return c;
}

int ct[N << 2], n;
void pt(int o, int v) { ct[o] = v; val[o] = node(v, 1, v, v); }
void pd(int o) { if(ct[o]) pt(o << 1, ct[o]), pt(o << 1 | 1, ct[o]), ct[o] = 0; }
void build(int o = 1, int l = 1, int r = V) {
	if(l == r) return val[o] = node(0, 1, 0, 0), void(); int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); val[o] = val[o << 1] + val[o << 1 | 1];
}
void upd(int xl, int xr, int v, int o = 1, int l = 1, int r = V) {
	if(xl <= l && r <= xr) return pt(o, v); int mid = l + r >> 1; pd(o);
	if(xl <= mid) upd(xl, xr, v, o << 1, l, mid); if(xr > mid) upd(xl, xr, v, o << 1 | 1, mid + 1, r);
	val[o] = val[o << 1] + val[o << 1 | 1];
}
node query(int xl, int xr, int o = 1, int l = 1, int r = V) {
	if(xl == l && xr == r) return val[o]; int mid = l + r >> 1; pd(o);
	if(xr <= mid) return query(xl, xr, o << 1, l, mid); else if(xl > mid) return query(xl, xr, o << 1 | 1, mid + 1, r);
	else return query(xl, mid, o << 1, l, mid) + query(mid + 1, xr, o << 1 | 1, mid + 1, r);
}
set < pii > s[N];

int solve(int l, int r, int h) {
	l += 2; r++; node t = query(l, r); int ans = t.cnt - 1; //cerr << "!" << t.mx << " " << t.cnt << endl;
	auto it = s[l - 1].lower_bound({ t.mx, inf }); bool hav = true;
	while(it != s[l - 1].end() && it->fi <= t.mx + h) {
		if(it->se <= t.mx) hav = false; ans++; s[l - 1].erase(it++);
	} if(it != s[l - 1].end() && it->se <= t.mx) hav = false;
	ans += hav && t.l != t.mx && query(l - 1, l - 1).mx >= t.mx;
	if(t.l != t.mx) s[l].insert({ t.mx, t.l + 1 });
	it = s[r + 1].lower_bound({ t.mx, inf }); hav = true;
	while(it != s[r + 1].end() && it->fi <= t.mx + h) {
		if(it->se <= t.mx) hav = false; ans++; s[r + 1].erase(it++);
	} if(it != s[r + 1].end() && it->se <= t.mx) hav = false;
	ans += hav && t.r != t.mx && query(r + 1, r + 1).mx >= t.mx;
	if(t.r != t.mx) s[r].insert({ t.mx, t.r + 1 }); upd(l, r, t.mx + h); return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("block.in", "r", stdin); freopen("block.out", "w", stdout);
#endif
	n = in; build(1, 1, V);
	while(n--) { int l = in, r = in, h = in; printf("%d\n", solve(l, r, h)); }
	return 0;
}
