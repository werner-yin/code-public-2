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
//constexpr int mod = 998244353;
constexpr int mod = 1e9 + 7;

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
	int val() { return x; }
	Z inv() const { assert(x); return qp(*this, mod - 2); }
	Z &operator += (const Z &t) { x = reduce(x + t.x); return *this; }
	Z &operator -= (const Z &t) { x = reduce(x - t.x); return *this; }
	Z &operator *= (const Z &t) { x = (ll)x * t.x % mod; return *this; }
	Z &operator /= (const Z &t) { return *this *= t.inv(); }
	friend Z operator + (const Z &a, const Z &b) { Z res = a; res += b; return res; }
	friend Z operator - (const Z &a, const Z &b) { Z res = a; res -= b; return res; }
	friend Z operator * (const Z &a, const Z &b) { Z res = a; res *= b; return res; }
	friend Z operator / (const Z &a, const Z &b) { Z res = a; res /= b; return res; }
};

int h[N], n;

pair < Z, Z > solve(int l, int r, int cut) {
	int mn = 1e9, w = 0; rep(i, l, r) chkmin(mn, h[i]);
	Z dp1, dp2; rep(i, l, r) if(h[i] == mn) w++;
	vector < pair < Z, Z > > pot;
	int lst = l;
	rep(i, l, r) {
		if(h[i] == mn) {
			if(lst <= i - 1) pot.eb(solve(lst, i - 1, mn));
			lst = i + 1;
		} 
	} if(lst <= r) pot.eb(solve(lst, r, mn));
	dp1 = 1, dp2 = 1;
	for(auto v : pot) dp1 *= v.fi, dp2 *= v.fi + v.se;
	dp1 *= qp(Z(2), mn - cut); dp2 *= qp(Z(2), w);
	Z ret = 1; for(auto v : pot) ret *= v.fi;
	dp2 += ret * (qp(Z(2), mn - cut) - 2);
	return { dp1, dp2 };
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) h[i] = in;
	auto ans = solve(1, n, 0); cout << ans.se.val() << endl;
	return 0;
}
