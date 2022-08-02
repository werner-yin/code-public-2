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

int H, L;
int p[N];
int dep[N];
Z tdep[N], tidep[N];

int lca(int x, int y) {
	//	cerr << x << " " << y << endl;
	while(dep[x] > dep[y]) x >>= 1;
	while(dep[y] > dep[x]) y >>= 1;
	while(x != y) x >>= 1, y >>= 1;
	return x;
}

Z ans = 0, ret = 0, vret = 0;

vec G[N];
int stk[N], top;
Z f[N], g[N], tval[N], val[N];

void dfs(int x) {
	f[x] += val[x] * tdep[x]; g[x] += tval[x] * tdep[x];
	//cerr << "!" << x << " " << f[x] << " " << val[x] * tdep[x] << endl;
	for(auto y : G[x]) {
		dfs(y);
		ret += f[x] * f[y] * tidep[x] * tidep[x >> 1];
		vret += g[x] * g[y] * tidep[x] * tidep[x >> 1];
		f[x] += f[y]; g[x] += g[y];
	}
}

void cdfs(int x) {
	f[x] = val[x] = g[x] = 0;
	for(auto y : G[x]) cdfs(y);
	G[x].clear();
}

void get(int lc) {
	vector < pair < int, Z > > pot; ret = vret = 0;
	rep(s, 0, (1 << H - dep[lc]) - 1) {
		pot.eb(p[s | (lc << H - dep[lc])], tdep[s | (lc << H - dep[lc])] * tidep[lc]);
	}
	sort(pot.begin(), pot.end(), [&](auto a, auto b) { return a.fi < b.fi; });
	top = 1; stk[top] = 1;
	for(auto v : pot) {
		int x = v.fi; if(x == 1) continue;
		int t = lca(stk[top], x);
		while(top > 1 && dep[t] <= dep[stk[top - 1]]) G[stk[top - 1]].eb(stk[top]), top--;
		if(t != stk[top]) G[t].eb(stk[top]), stk[top] = t;
		stk[++top] = x;
	}
	rep(i, 1, top - 1) G[stk[i]].eb(stk[i + 1]);
	for(auto v : pot) val[v.fi] = v.se, tval[v.fi] = v.se * tdep[lc] * tidep[lc >> 1];
	dfs(1); cdfs(1); ans += ret * lc; ans -= vret * (lc >> 1);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	H = in, L = 1 << H - 1;
	rep(i, 1, L) p[i + L - 1] = in + L - 1;
	tdep[0] = tidep[0] = 1; rep(i, 1, L << 1) dep[i] = dep[i >> 1] + 1, tdep[i] = tdep[i >> 1] * i, tidep[i] = tdep[i].inv();
	rep(i, 1, L - 1) get(i); cout << ans << endl;
	return 0;
}
