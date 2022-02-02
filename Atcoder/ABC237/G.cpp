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
using info = array< int, 2 >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x > y ? x : y; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 2e5 + 10;

int n, Q, X;
int p[N], C[N], L[N], R[N];

struct tag { int x; tag(int _x = -1) : x(_x) {} bool hav() { return x != -1; } };
info operator + (info a, info b) { return { a[0] + b[0], a[1] + b[1] }; }
void operator += (info &a, tag b) { if(b.x != -1) { a[b.x] += a[!b.x], a[!b.x] = 0; } }
void operator += (tag &a, tag b) { if(b.x != -1) a = b; }

info initval[N];

template < class valtp, class tagtp > struct seg {
	vector < valtp > val; vector < tagtp > tg; const int n;
	void build(int o, int l, int r) {
		tg[o] = tagtp(); if(l == r) return val[o] = initval[l], void(); int mid = l + r >> 1; 
		build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); val[o] = val[o << 1] + val[o << 1 | 1];
	}
	seg(int _n) : n(_n) { val = vector < valtp > (n + 2 << 2, valtp()), tg = vector < tagtp > (n + 2 << 2, tagtp()); build(1, 1, n); }
	void pd(int o) {
		if(tg[o].hav()) { val[o << 1] += tg[o]; val[o << 1 | 1] += tg[o]; tg[o << 1] += tg[o]; tg[o << 1 | 1] += tg[o]; }
		tg[o] = tagtp();
	}
	void upd(const int &xl, const int &xr, const tagtp &v, const int &o, const int &l, const int &r) {
		if(xl <= l && r <= xr) return val[o] += v, tg[o] += v, void(); int mid = l + r >> 1; pd(o);
		if(xl <= mid) upd(xl, xr, v, o << 1, l, mid); if(xr > mid) upd(xl, xr, v, o << 1 | 1, mid + 1, r);
		val[o] = val[o << 1] + val[o << 1 | 1];
	}
	void upd(int xl, int xr, tagtp v) { if(xl <= xr) upd(xl, xr, v, 1, 1, n); }
	valtp query(const int &xl, const int &xr, const int &o, const int &l, const int &r) {
		if(xl == l && xr == r) return val[o]; int mid = l + r >> 1; pd(o);
		if(xr <= mid) return query(xl, xr, o << 1, l, mid); else if(xl > mid) return query(xl, xr, o << 1 | 1, mid + 1, r);
		else return query(xl, mid, o << 1, l, mid) + query(mid + 1, xr, o << 1 | 1, mid + 1, r);
	}
	valtp query(int xl, int xr) { return query(xl, xr, 1, 1, n); }
};

int solve(int X) {	
	rep(i, 1, n) initval[i] = { p[i] < X, p[i] >= X };
	seg < info, tag > T(n);
	rep(i, 1, Q) {
		auto v = T.query(L[i], R[i]); 
		if(C[i] == 1) T.upd(L[i], L[i] + v[0] - 1, tag(0)), T.upd(L[i] + v[0], R[i], tag(1));
		else T.upd(L[i], L[i] + v[1] - 1, tag(1)), T.upd(L[i] + v[1], R[i], tag(0));
	} int res = 0;
	rep(i, 1, n) if(T.query(i, i)[1]) res ^= i;
	return res;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, Q = in, X = in; rep(i, 1, n) p[i] = in;
	rep(i, 1, Q) C[i] = in, L[i] = in, R[i] = in;
	printf("%d\n", solve(X) ^ solve(X + 1));
	return 0;
}
