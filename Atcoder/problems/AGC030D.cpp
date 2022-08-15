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

const int N = 3010 + 10;
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

/* prime, mu, phi */
int mu[N], phi[N], pnum, pri[N];
bool v[N];

void shai(int l) {
	mu[1] = phi[1] = 1;
	rep(i, 2, l) {
		if(!v[i]) pri[++pnum] = i, mu[i] = -1, phi[i] = i - 1;
		rep(j, 1, pnum) {
			int t = i * pri[j]; if(t > l) break; v[t] = 1; 
			if(i % pri[j] == 0) { mu[t] = 0, phi[t] = phi[i] * pri[j]; break; }
			phi[t] = phi[i] * phi[pri[j]], mu[t] = -mu[i];
		}
	} 
}

const Z inv2 = Z(2).inv();

Z f[N][N], pt;
int a[N], x[N], y[N], n, q;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, q = in;
	rep(i, 1, n) a[i] = in;
	rep(i, 1, q) x[i] = in, y[i] = in;
	rep(i, 1, n) rep(j, 1, n) if(a[i] > a[j]) f[i][j] += 1;
	pt = 1;
	rep(i, 1, q) {
		int x = ::x[i], y = ::y[i];
		rep(j, 1, n) if(j != y && j != x) {
			Z u = f[x][j], v = f[y][j];
			f[y][j] = f[x][j] = (u + v) * inv2;
		}
		rep(j, 1, n) if(j != y && j != x) {
			Z u = f[j][x], v = f[j][y];
			f[j][y] = f[j][x] = (u + v) * inv2;
		}
		Z u = f[x][y], v = f[y][x];
		f[x][y] = f[y][x] = (u + v) * inv2;
		pt *= 2;
	}
	Z ans = 0;
	rep(i, 1, n) rep(j, 1, i - 1) ans += f[j][i] * pt;
	cout << ans << endl;
	return 0;
}
