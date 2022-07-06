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

Z ans = 1;

int n, a[N], indeg[N];
bool vis[N];
int stk[N], top;

void dfs(int x) {
	vis[x] = true; stk[++top] = a[x];
	rep(i, 1, n) if(!vis[i] && (a[x] % a[i] == 0 || a[i] % a[x] == 0)) dfs(i);
}

int cnt[1 << 15], id[N];
Z f[20][1 << 15];

void calc() {
	int U = 1, tot = -1; rep(i, 0, top) if(indeg[i] == 0) U <<= 1, id[i] = ++tot;
	U--; vec pot; rep(s, 0, U) cnt[s] = 0;
	rep(i, 0, top) if(indeg[i]) {
		int stu = 0; rep(j, 0, top) if(stk[i] % stk[j] == 0 && indeg[j] == 0) stu |= 1 << id[j];
		pot.eb(stu);
		rep(s, 0, U) if((s & stu) == stu) cnt[s]++;
	}
	rep(i, 1, top - tot) rep(s, 0, U) f[i][s] = 0;
	for(auto v : pot) f[1][v] += 1;
	rep(i, 1, top - tot - 1) {
		rep(s, 0, U) if(f[i][s].val()) {
			if(cnt[s] > i) f[i + 1][s] += f[i][s] * (cnt[s] - i);
			for(auto v : pot)
				if((s & v) && (s | v) > s) {
					f[i + 1][s | v] += f[i][s];
				}
		}
	} Z ret = 0; rep(s, 0, U) ret += f[top - tot][s];
	ans *= ret * ifac[top - tot - 1];
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in; init(n);
	int tot = 0;
	rep(x, 1, n) if(!vis[x]) {
		top = -1; dfs(x);
		rep(i, 0, top) indeg[i] = 0;
		rep(i, 0, top) rep(j, 0, top) if(stk[i] % stk[j] == 0 && i ^ j) indeg[i]++;
		int cnt = 0; rep(i, 0, top) cnt += !indeg[i];
		if(top - cnt <= 0) continue;
		/* cerr << top << " " << cnt << endl; */ calc(); tot += top - cnt;
	} ans *= fac[tot]; cout << ans.val() << endl;
	return 0;
}
