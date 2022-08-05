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
constexpr int mod = 998244353;
//constexpr int mod = 1e9 + 7;

int reduce(int x) {
	if(x < 0) x += mod;
	if(x >= mod) x -= mod;
	return x;
}

template < typename T > T qp(T x, ll t) { T res = 1; for(; t; t >>= 1, x *= x) if(t & 1) res *= x; return res; }

struct Z { // modint
	int x;
	Z(int x = 0) : x(reduce(x)) {}
	Z(ll x) : x(reduce(x % mod)) {}
	Z operator -() const { return Z(reduce(mod - x)); }
	int val() const { return x; }
	Z inv() const { assert(x); return qp(*this, mod - 2); }
	Z &operator += (const Z &t) { x = reduce(x + t.x); return *this; }
	Z &operator -= (const Z &t) { x = reduce(x - t.x); return *this; }
	Z &operator *= (const Z &t) { x = (ll)x * t.x % mod; return *this; }
	Z &operator /= (const Z &t) { return *this *= t.inv(); }
	friend Z operator + (const Z &a, const Z &b) { Z res = a; res += b; return res; }
	friend Z operator - (const Z &a, const Z &b) { Z res = a; res -= b; return res; }
	friend Z operator * (const Z &a, const Z &b) { Z res = a; res *= b; return res; }
	friend Z operator / (const Z &a, const Z &b) { Z res = a; res /= b; return res; }
	friend ostream & operator << (ostream &out, const Z &x) {
		out << x.val();
		return out;
	}
};


Z fac[N], ifac[N];
Z C(int x, int y) { return x < 0 || y < 0 || x < y ? Z(0) : fac[x] * ifac[y] * ifac[x - y]; }
void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * Z(i); ifac[l] = fac[l].inv();
	per(i, l - 1, 0) ifac[i] = ifac[i + 1] * Z(i + 1);
}

int n, m, b[N], tot, Q, L[N], R[N], X[N], lim[N];

int getpos(int x) { return lower_bound(b + 1, b + tot + 1, x) - b; }

int val[N << 2];

void build(int o = 1, int l = 1, int r = n) {
	val[o] = m; if(l == r) return; int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
}

void upd(int xl, int xr, int v, int o = 1, int l = 1, int r = n) {
	if(xl <= l && r <= xr) return chkmin(val[o], v); int mid = l + r >> 1;
	if(xl <= mid) upd(xl, xr, v, o << 1, l, mid); if(xr > mid) upd(xl, xr, v, o << 1 | 1, mid + 1, r); 
}

void getall(int o = 1, int l = 1, int r = n) {
	if(l == r) return lim[l] = val[o], void(); int mid = l + r >> 1; chkmin(val[o << 1], val[o]), chkmin(val[o << 1 | 1], val[o]);
	getall(o << 1, l, mid), getall(o << 1 | 1, mid + 1, r);
}

vec dpot[N];
veg qpot[N];

Z ans = 1;

namespace vsolve { 
	int a[N], n;
	namespace seg {
		Z val[N << 2], mul[N << 2];
		void pu(int o) { val[o] = val[o << 1] + val[o << 1 | 1]; }
		void pt(int o, Z v) { mul[o] *= v, val[o] *= v; }
		void pd(int o) { if(mul[o].val() != 1) pt(o << 1, mul[o]), pt(o << 1 | 1, mul[o]), mul[o] = 1; }
		void build(int o = 1, int l = 0, int r = n) {
			mul[o] = 1; val[o] = 0; if(l == r) return; int mid = l + r >> 1;
			build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
		}
		void upd(int xl, int xr, Z v, int o = 1, int l = 0, int r = n) {
			if(xl <= l && r <= xr) return pt(o, v); int mid = l + r >> 1; pd(o);
			if(xl <= mid) upd(xl, xr, v, o << 1, l, mid); if(xr > mid) upd(xl, xr, v, o << 1 | 1, mid + 1, r);
			pu(o);
		}
		void updpos(int pos, Z v, int o = 1, int l = 0, int r = n) {
			if(l == r) return val[o] = v, void(); int mid = l + r >> 1; pd(o);
			if(pos <= mid) updpos(pos, v, o << 1, l, mid); else updpos(pos, v, o << 1 | 1, mid + 1, r);
			pu(o);
		}
	}
	int lim[N];
	void solve(vec pot, veg qpot, Z val) {
		if(!pot.size() && qpot.size()) return ans = 0, void();
		n = 0; for(auto v : pot) a[++n] = v;
		//cerr << val << " : "; for(auto v : pot) cerr << v << " "; cerr << endl;
		rep(i, 0, n) lim[i] = 0; seg :: build(); seg :: updpos(0, 1);
		for(auto [l, r] : qpot) {
			l = lower_bound(a + 1, a + n + 1, l) - a;
			r = upper_bound(a + 1, a + n + 1, r) - a - 1;
			if(l > r) return ans = 0, void();
			chkmax(lim[r], l);
		}
		rep(i, 1, n) {
			Z p = seg :: val[1];
			if(lim[i] > 0) seg :: upd(0, lim[i] - 1, 0);
			seg :: upd(0, n, val);
			seg :: updpos(i, p);
		} ans = ans * seg :: val[1];
	}

}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, Q = in; b[++tot] = m;
	rep(i, 1, Q) {
		L[i] = in, R[i] = in, X[i] = in, b[++tot] = X[i];
	}
	sort(b + 1, b + tot + 1); tot = unique(b + 1, b + tot + 1) - b - 1;
	rep(i, 1, Q) X[i] = getpos(X[i]);
	m = getpos(m);
	build();
	rep(i, 1, Q) 
		upd(L[i], R[i], X[i]);
	getall();
	rep(i, 1, n) dpot[lim[i]].eb(i);
	rep(i, 1, Q) qpot[X[i]].eb(L[i], R[i]);
	rep(i, 1, tot) vsolve :: solve(dpot[i], qpot[i], b[i]);
	cout << ans << endl;
	return 0;
}
