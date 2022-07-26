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

map < string, Z > f, g;

Z calc(string s);

Z tcalc(string s) {
	if(!s.size()) return 0;
	if(g.count(s)) return g[s];
	Z ans = 0;
	rep(j, 1, (int)s.size() - 1) if(s.size() % j == 0) {
		string ret(j, '1');
		rep(k, 0, (int)s.size() - 1) chkmin(ret[k % j], s[k]);
		ans += calc(ret);
	} //cerr << "TCALC " << s << " : " << ans.val() << endl;
	return g[s] = ans;
}

Z calc(string s) {
	if(!s.size()) return 1;
	if(f.count(s)) return f[s];
	Z ans = 0, ret = 1;
	for(auto v : s) if(v == '1') ret *= 2;
	ans += ret;
	rep(j, 0, int(s.size()) - 1)
		rep(k, 0, j - 1) {
		auto get = [&](int l, int r) {
			string t; rep(i, l, r) t += s[i];
			return t;
		};
		auto vcalc = [&](int l, int r) {
			Z ret = 1; rep(i, l, r) if(s[i] == '1') ret *= 2;
			return ret;
		};
		ans += vcalc(0, k - 1) * tcalc(get(k, j)) * calc(get(j + 1, int(s.size() - 1)));
		//ans += calc(get(k, j - 1)) * tcalc(get(j, int(s.size() - 1)));
		//ans -= tcalc(get(k, j - 1)) * tcalc(get(j, int(s.size() - 1)));
	} return f[s] = ans;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	string s; cin >> s; cout << calc(s).val() << endl; //cerr << s.size() << " " << f.size() << " " << g.size() << endl;
	return 0;
}
