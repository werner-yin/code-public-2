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
};

Z fac[N], ifac[N];
Z C(int x, int y) { return x < 0 || y < 0 || x < y ? Z(0) : fac[x] * ifac[y] * ifac[x - y]; }
void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * Z(i); ifac[l] = fac[l].inv();
	per(i, l - 1, 0) ifac[i] = ifac[i + 1] * Z(i + 1);
}

Z pw[N];
vec G[N];
int val[3][N], m, n, len;
Z f[3][N];

void init(int *val) {
	m = in; rep(i, 1, n) G[i].clear();
	rep(i, 1, m) {
		int a = in, b = in;
		if(a > b) swap(a, b);
		G[a].eb(b);
	}
	per(i, n, 1) {
		vec pot; for(auto y : G[i]) pot.eb(val[y]);
		sort(pot.begin(), pot.end()); pot.resize(unique(pot.begin(), pot.end()) - pot.begin());
		pot.eb(pot.size() + 114);
		rep(j, 0, (int)pot.size() - 1)
			if(pot[j] != j) {
				val[i] = j; break;
			}
	}
}

const Z B = Z(ll(1e18));
const Z inv2 = Z(2).inv();

void FWT(Z *f, int op = 1) {
	for(int h = 2; h <= len; h <<= 1) {
		for(int i = 0, j = h >> 1; i < len; i += h) {
			for(int k = 0; k < j; k++) {
				Z u = f[i | k], v = f[i | j | k];
				f[i | k] = u + v, f[i | j | k] = u - v;
				if(op == -1) f[i | k] *= inv2, f[i | j | k] *= inv2;
			}
		}
	}
}

Z ret[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	init(val[0]), init(val[1]), init(val[2]);
	pw[0] = 1; rep(i, 1, n * 3) pw[i] = pw[i - 1] * B;
	len = 1; while(len < n) len <<= 1;
	rep(i, 0, 2) {
		rep(j, 1, n) f[i][val[i][j]] += pw[j];
		FWT(f[i]);
	}
	Z ans = 0;
	rep(i, 0, len - 1) ret[i] = f[0][i] * f[1][i] * f[2][i];
	FWT(ret, -1); cout << ret[0].val() << endl;
	return 0;
}
