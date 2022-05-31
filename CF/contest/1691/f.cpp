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

Z fac[N], ifac[N];
Z C(int x, int y) { return x < 0 || y < 0 || x < y ? Z(0) : fac[x] * ifac[y] * ifac[x - y]; }
void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * Z(i); ifac[l] = fac[l].inv();
	per(i, l - 1, 0) ifac[i] = ifac[i + 1] * Z(i + 1);
}

int n, K, siz[N], fa[N];
Z ret[N], ans;
vec G[N];

void dfs(int x, int p) {
	siz[x] = 1; fa[x] = p;
	for(auto y : G[x]) if(y ^ p) {
			dfs(y, x); siz[x] += siz[y]; ret[x] += C(siz[y], K);
		}
	ret[x] += C(n - siz[x], K);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	init(n); dfs(1, 0);
	rep(x, 1, n) {
		for(auto y : G[x])
			if(y == fa[x]) {
				Z t = (n - siz[x]) * (C(siz[x], K) - (ret[x] - C(n - siz[x], K))) * siz[x];
				ans += t;
			} else {
				Z t = siz[y] * (C(n - siz[y], K) - (ret[x] - C(siz[y], K))) * (n - siz[y]);
				ans += t;
			}
		ans += (C(n, K) - ret[x]) * n;
	}
	cout << ans.val() << endl;
	return 0;
}
