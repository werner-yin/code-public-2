#include <bits/stdc++.h>
#include "atcoder/convolution.hpp"

#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using vec = vector < int >;

const int N = 1e6 + 10;
const int mod = 998244353;

ll h, w, fac[N], ifac[N], ans;

ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }
ll C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * ifac[y] % mod * ifac[x - y] % mod; }
void init(int l) {
	rep(i, (fac[0] = 1), l) fac[i] = 1ll * fac[i - 1] * i % mod; ifac[l] = qp(fac[l], mod - 2);
	per(i, l - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
}

vector < ll > operator * (const vector < ll > &a, const vector < ll > &b) {
	vector < ll > c = atcoder :: convolution < mod > (a, b);
	rep(i, w, (int)c.size() - 1) (c[i % w] += c[i]) %= mod; c.resize(w); return c;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	cin >> h >> w; 
	if(h % 2 == 0 && w % 2 == 0) return puts("2"), 0;
	if(h < w) swap(h, w); if(w % 2 == 0) swap(h, w);
	if(h < w) {
		init(h);
		rep(x, 0, h) if(x % w == (h - x) % w) ans = (ans + C(h, x)) % mod;
	} else {
		vector < ll > pt(w, 0); pt[1] = pt[w - 1] = 1;
		vector < ll > cur(w, 0); cur[0] = 1;
		for(; h; h >>= 1, pt = pt * pt) if(h & 1ll) cur = cur * pt;
		ans = cur[0];
	} ans = ans * w % mod; cout << ans << endl; return 0;
}
