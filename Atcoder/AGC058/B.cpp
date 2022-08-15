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

Z f[N], pre[N], suf[N], tval[N], tf[N];
int n, p[N], ind[N];
bool ok[N], pok[N];
Z tr[N];
void add(int x, Z v) { for(; x <= n; x += x & -x) tr[x] += v; }
Z query(int x) { Z ret = 0; for(; x; x -= x & -x) ret += tr[x]; return ret; }

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) p[i] = in, ind[p[i]] = i;
	rep(i, 1, n) ok[i] = 0;
	int mx = 0;
	rep(i, 1, n) chkmax(mx, p[i]), ok[mx] = true;
	rep(i, 1, n) if(ok[i]) f[i] = 1;
	//rep(i, 1, n) cerr << f[i]  << " "; cerr << endl;
	rep(i, 2, n) {
		rep(j, 1, n) ok[j] = 0;
		int mx = 0;
		rep(j, i, n) {
			chkmax(mx, p[j]);
			ok[mx] = true;
		}
		mx = 0;
		rep(j, 1, n) pok[j] = 0;
		per(j, i, 1) {
			chkmax(mx, p[j]);
			pok[mx] = true;
		}
		rep(j, 1, n) tf[j] = f[j];
		rep(j, 1, n) pre[j] = pre[j - 1] + f[j]; //(ok[j] && j != p[i] ? 0 : f[j]);
		per(j, n, 1) suf[j] = suf[j + 1] + (ind[j] > i ? 0 : f[j]);
		rep(j, 1, n) tr[j] = 0;
		rep(j, 1, n) {
			tval[p[j]] = 0;
			tval[p[j]] = query(n) - query(p[j]); add(p[j], f[p[j]]);
		}
		rep(j, 1, n) {
			if(p[i] > j) f[j] = 0;
			else {
				if(ok[j]) f[j] += pre[j - 1] + suf[j + 1];
				else if(j > p[i] && pok[j]) {
					//rep(k, j + 1, n) if(ind[k] < ind[j]) f[j] += tf[k];
					f[j] += tval[j];
				}
			}
		}
		//rep(j, 1, n) cerr << f[j] << " "; cerr << endl;
	}
	Z ans = 0;
	rep(i, 1, n) ans += f[i];
	cout << ans << endl;
	return 0;
}
