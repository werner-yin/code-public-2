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

const int N = 610;
const int T = 14;
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

Z fac[N], ifac[N];
Z C(int x, int y) { return x < 0 || y < 0 || x < y ? Z(0) : fac[x] * ifac[y] * ifac[x - y]; }
void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * Z(i); ifac[l] = fac[l].inv();
	per(i, l - 1, 0) ifac[i] = ifac[i + 1] * Z(i + 1);
}

int n, m, lg[1 << T], s[1 << T], U, bt[1 << T];
vec G[N];
Z f[1 << T], g[T + 2][1 << T];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; init(m); rep(i, 1, m) { int u = in - 1, v = in - 1; G[u].eb(v), G[v].eb(u); }
	U = 1 << n; U--; rep(s, 2, U) lg[s] = lg[s >> 1] + 1;
	rep(i, 0, U) bt[i] = __builtin_popcount(i);
	rep(s, 1, U) {
		int x = __builtin_ctz(s);
		::s[s] = ::s[s ^ 1 << x];
		for(auto y : G[x]) if(s >> y & 1) ::s[s]++;
	}
	rep(i, 0, n - 1) f[1 << i] = 1;
	f[0] = 1;
	rep(s, 1, U) {
		for(int tv = U ^ s, t = tv; t; t = (t - 1) & tv) {
			if(t <= s) f[s | t] += f[t] * f[s] * C(bt[t] + bt[s] - 2, bt[t] - 1) * (::s[s | t] - ::s[s] - ::s[t]);
		}
		//cerr << f[s].val() << " ";
	}
	g[0][0] = 1;
	rep(i, 0, n - 1) {
		rep(s, 0, U)
			for(int tv = U ^ s, t = tv; t; t = (t - 1) & tv) {
				if(bt[t] > 1 && __builtin_ctz(t) < __builtin_ctz(s) && i + bt[t] - 1 < n) g[i + bt[t] - 1][s | t] += f[t] * g[i][s] * C(bt[t] + i - 1, i);
				//if(t == 0) break;
			}
		Z ret = 0; rep(s, 0, U) ret += g[i][s];
		//cerr << "!" << ret.val() << endl;
		//rep(s, 0, U) cerr << g[i][s].val() << " "; cerr << endl;
		if(i >= 1) {
			cout << (ret * qp(Z(m), i).inv()).val() << endl;
		}
	}
	return 0;
}
