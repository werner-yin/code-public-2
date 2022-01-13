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
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) >> 1;
const int inv3 = (mod + 1) / 3;

ll n, lim, sp1[N], sp2[N], g1[N], g2[N], w[N];
int ind1[N], ind2[N], tot;
int pri[N / 10], pnum;
bool v[N];

void shai(int l) {
	rep(i, 2, l) {
		if(!v[i]) {
			pri[++pnum] = i;
			sp1[pnum] = (sp1[pnum - 1] + i) % mod;
			sp2[pnum] = (sp2[pnum - 1] + 1ll * i * i) % mod;
		}
		rep(j, 1, pnum) {
			if(pri[j] * i > l) break;
			v[pri[j] * i] = true; if(i % pri[j] == 0) break;
		}
	}
}

int S(ll x, int y) {
	if(x < pri[y]) return 0;
	ll res = 0;
	res += g2[x <= lim ? ind1[x] : ind2[n / x]] - sp2[y - 1];
	res -= g1[x <= lim ? ind1[x] : ind2[n / x]] - sp1[y - 1];
	res = (res % mod + mod) % mod;
	rep(k, y, pnum) {
		if(1ll * pri[k] * pri[k] > x) break;
		ll cur = pri[k];
		for(int c = 1; cur <= x; cur *= pri[k], c++) {
			res += cur % mod * ((cur - 1) % mod) % mod * (S(x / cur, k + 1) + (c != 1)) % mod;
			res %= mod;
		}
	} return res % mod;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = lin, lim = sqrtl(n);
	shai(lim * 2);
	for(ll i = 1; i <= n; i++) {
		++tot, w[tot] = (n / i); ll v = w[tot] % mod;
		g1[tot] = (v * (v + 1) / 2 - 1) % mod;
		g2[tot] = (v * (v + 1) % mod * (v * 2 + 1) % mod * inv2 % mod * inv3 % mod - 1) % mod;
		if(w[tot] <= lim) ind1[w[tot]] = tot; else ind2[n / w[tot]] = tot;
		i = n / (n / i);
	}
	rep(i, 1, pnum) { 
		int p = pri[i]; ll x1 = sp1[i - 1], x2 = sp2[i - 1];
		rep(x, 1, tot) {
			if(1ll * p * p > w[x]) break;
			int y = w[x] / p <= lim ? ind1[w[x] / p] : ind2[n / (w[x] / p)];
			g1[x] = (g1[x] - 1ll * p * (g1[y] - x1) % mod + mod) % mod;
			g2[x] = (g2[x] - 1ll * p * p % mod * (g2[y] - x2) % mod + mod) % mod;
		}
	}
	printf("%d\n", (S(n, 1) + 1) % mod);
	return 0;
}
