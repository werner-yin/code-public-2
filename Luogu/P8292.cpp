#include <bits/stdc++.h>

#define in read<int>()
#define lin read<ll>()
#define fi first
#define se second
#define eb emplace_back
#define ep emplace
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using db = double;
using vec = vector < int >;
using pii = pair < int, int >;
using veg = vector < pii >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x < y ? y : x; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 1e6 + 10;
const int mod = 998244353;
const int B = 14; // 小质数个数
const int T = 310; // 大质数
const int U = (1 << B) - 1;
const int M = 1510;
const int inv2 = (mod + 1) >> 1;

int mxfac[N], pri[N], num[N], pw[N], pnum, ind[N], ipw[N];
bool v[N];
int a[T][1 << B | 5], b[T][1 << B | 5], n, m;
//int pre[T][1 << B | 5], suf[T][1 << B | 5];
int ans[1 << B | 5];

ll qp(ll x, int t) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

void shai(int l) {
	rep(i, 2, l) {
		if(!v[i]) pri[++pnum] = i, ind[i] = pnum, mxfac[i] = pnum;
		rep(j, 1, pnum) {
			if(pri[j] * i > l) break;
			mxfac[pri[j] * i] = j; v[pri[j] * i] = true; if(i % pri[j] == 0) break;
		}
	}
}

void factor(int x) {
	int pp = 0; int stu = 0;
	while(x > 1) {
		int t = mxfac[x];
		if(t <= B) stu |= 1 << t - 1;
		else pp = t;
		while(x % pri[t] == 0) x /= pri[t];
	}
	b[pp][stu]++;
}

void upd(int &x) { x = x + (x >> 31 & mod); }

void FMT(int *f) { rep(i, 0, 13) rep(j, 0, U) if(j >> i & 1) upd(f[j] += f[j ^ 1 << i] - mod); }
void IFMT(int *f) { rep(i, 0, 13) rep(j, 0, U) if(j >> i & 1) upd(f[j] -= f[j ^ 1 << i]); }
void nmul(int *f, int *g) { // f = f * g
	rep(i, 0, U) f[i] = 1ll * f[i] * g[i] % mod;
}
void cmul(int *f, int *g) { // mul & no mul
	rep(i, 0, U) f[i] = 1ll * f[i] * (g[i] + 1) % mod;
}
void reset(int *f) { rep(i, 0, U) f[i] = 1; }
void copy(int *f, int *g) { // f = g
	rep(i, 0, U) f[i] = g[i];
}

int stu[M];
int cur[1 << B | 5];

namespace sub2 {
	void solve() {
		rep(i, 1, m) {
			rep(j, 0, U) ans[j] = cur[j];
			int cnt = in; vec pot;
			while(cnt--) {
				int x = ind[in];
				if(x <= B) stu[i] |= 1 << x - 1;
				else pot.eb(x);
			}
			sort(pot.begin(), pot.end()); pot.resize(unique(pot.begin(), pot.end()) - pot.begin()); // 去重！
			for(auto v : pot) nmul(ans, a[v]);
			IFMT(ans); int ret = 0;
			rep(j, 0, U) if((stu[i] & j) == stu[i]) upd(ret += ans[j] - mod);
			printf("%d\n", ret);
		} 
	}
}

int main() {
	freopen("card.in", "r", stdin); freopen("card.out", "w", stdout);
	shai(2000); n = in;
	rep(i, 1, n) factor(num[i] = in);
	pw[0] = 1; rep(i, 1, n) pw[i] = pw[i - 1] * 2ll % mod;
	ipw[0] = 1; rep(i, 1, n) ipw[i] = 1ll * ipw[i - 1] * inv2 % mod;
	rep(i, 0, U) cur[i] = 1;
	rep(i, 0, pnum) {
		FMT(b[i]);
		rep(j, 0, U) a[i][j] = b[i][j] <= n ? pw[b[i][j]] % mod : qp(2, b[i][j]) % mod;
		nmul(cur, a[i]);
		rep(j, 0, U) a[i][j] = b[i][j] <= n ? 1ll * ipw[b[i][j]] * (pw[b[i][j]] + mod - 1) % mod : qp(inv2, b[i][j]) * (qp(2, b[i][j]) + mod - 1) % mod;
	} 
	m = in;
	sub2 :: solve();
	return 0;
}
