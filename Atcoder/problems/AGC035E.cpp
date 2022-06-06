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

const int N = 160;
//constexpr int mod = 1e9 + 7;

int mod;

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

Z pw[N], f[2][N][N]; // f[o][i][j] : i = 0 : 不延伸; i > 0 延伸 i - 1 长度，只有延伸的长度 < K 才行; j : 右侧链条延伸长度
int n, K;

void solve1() {
	int o = 0; rep(i, 0, K / 2) f[o][0][i] = K / 2 - i ? pw[K / 2 - i - 1] : 1;
	rep(pos, 1, n) {
		rep(x, 0, K) rep(y, 0, n) f[o ^ 1][x][y] = 0;
		rep(x, 0, K) rep(y, 0, n) f[o ^ 1][0][0] += f[o][x][y]; // 两个都不选。
		rep(x, 1, K - 1) rep(y, 0, n) f[o ^ 1][x + 1][0] += f[o][x][y]; // < K
		rep(y, 0, n) f[o ^ 1][0][0] += f[o][0][y];
		// 只选左边的。
		if(pos + K <= n) { 
			rep(x, 0, K) rep(y, 0, n) f[o ^ 1][0][y + 1] += f[o][x][y];
		}
		// 只选右边的。
		if(pos + K <= n) {
			rep(x, 1, K) rep(y, 0, n)
				if(max(x + 1, y + 1) <= K)
					f[o ^ 1][max(x + 1, y + 1)][y + 1] += f[o][x][y];
				else break;
			rep(x, 0, 0) rep(y, 0, n)
				if(y + 1 <= K)
					f[o ^ 1][y + 1][y + 1] += f[o][x][y];
				else break;
		} // 左右的都选。
		o ^= 1; pos++;
		//cerr << pos - 1 << endl;
		//rep(x, 0, K) rep(y, 0, n) cerr << x << " " << y << " " << f[o][x][y].val() << endl;
	}
	Z ans = 0; rep(x, 0, K) rep(y, 0, n) ans += f[o][x][y];
	cout << ans.val() << endl;
}

Z g[N][N];

void solve2() {
	K >>= 1; K++;
	g[0][0] = 1;
	rep(i, 1, n / 2 + 1) {
		rep(j, 0, min(i - 1, K - 1)) 
			g[i][j + 1] += g[i - 1][j], g[i][0] += g[i - 1][j];
	}
	Z ans1 = 0, ans2 = 0;
	rep(i, 0, K - 1) ans1 += g[(n + 1) / 2][i];
	rep(i, 0, K - 1) ans2 += g[n / 2][i];
	ans1 *= ans2; cout << ans1.val() << endl;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in, mod = in; pw[0] = 1; rep(i, 1, n) pw[i] = pw[i - 1] * 2;
	if(K & 1) solve1(); else solve2(); return 0;
}
