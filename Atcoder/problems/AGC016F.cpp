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

const int N = 15;
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

Z pw[N * N], f[1 << N];
bool ed[N][N];
int n, cnt[N][1 << N], ctz[1 << N], m, U;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, U = (1 << n) - 1;
	rep(i, 1, m) {
		int u = in - 1, v = in - 1;
		ed[u][v] = true;
	}
	rep(s, 1, U) ctz[s] = __builtin_ctz(s);
	rep(i, 0, n - 1) {
		rep(s, 1, U) {
			int x = ctz[s];
			cnt[i][s] = cnt[i][s ^ 1 << x] + ed[i][x];
		}
	}
	pw[0] = 1; rep(i, 1, m) pw[i] = pw[i - 1] + pw[i - 1];
	rep(s, 0, U) if((s & 3) == 3) {
		f[s] = 1;
		for(int t = (s - 1) & s; t; t = (t - 1) & s) if((t & 1) == (t >> 1 & 1)) {
				if(t & 1) {
					Z v = 1;
					rep(i, 0, n - 1) if(s >> i & 1) {
						if(t >> i & 1) v *= pw[cnt[i][t ^ s]] - 1;
						else v *= pw[cnt[i][t]];
					} f[s] += f[t] * v;
				} else {
					Z v = 1;
					rep(i, 0, n - 1) if(s >> i & 1) {
						if(t >> i & 1) v *= pw[cnt[i][t ^ s]] - 1, v *= pw[cnt[i][t]];
						else v *= pw[cnt[i][t]];
					} f[s] += v;
				}
			}
	} cout << (pw[m] - f[U]).val() << endl; return 0;
}
