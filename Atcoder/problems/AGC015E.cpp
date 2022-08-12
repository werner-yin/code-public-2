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

int x[N], v[N], id[N], b[N], p[N];
int n, l[N], r[N];
Z f[N], s[N], ans;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) x[i] = in, v[i] = b[i] = in, id[i] = i;
	sort(id + 1, id + n + 1, [&](int a, int b) { return x[a] < x[b]; });
	sort(b + 1, b + n + 1);
	rep(i, 1, n) {
		int pos = lower_bound(b + 1, b + n + 1, v[id[i]]) - b;
		p[i] = pos;
	}
	rep(i, 1, n) r[i] = max(r[i - 1], p[i]);
	l[n] = p[n];
	per(i, n - 1, 1) l[i] = min(l[i + 1], p[i]);
	int pos = 0; f[0] = s[0] = 1;
	rep(i, 1, n) {
		//cerr << l[i] << " " << r[i] << endl;
		while(pos <= i && r[pos] < l[i] - 1) pos++;
		f[i] = s[i - 1] - (pos == 0 ? 0 : s[pos - 1]); s[i] = s[i - 1] + f[i];
		if(r[i] == n) ans += f[i];
	} cout << ans << endl;
	return 0;
}
