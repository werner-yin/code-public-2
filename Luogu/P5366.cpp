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

int n, G, L, Q, cnt[710], stu[710], s[1 << 16], al, U, ind[1 << 16];
int f[650][1 << 16], g[650][1 << 16], h[650][1 << 16], ans[710], vs[710];
int p[N], c[N], tot;

ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

void getfac(int x) {
	rep(i, 2, x) {
		if(i * i > x) break; if(x % i) continue;
		p[++tot] = i; while(x % i == 0) x /= i, c[tot]++;
	} if(x > 1) p[++tot] = x, c[tot] = 1;
}

int calc(int x) {
	int res = 0;
	rep(i, 1, tot) {
		int ct = 0; while(x % p[i] == 0) x /= p[i], ct++;
		if(ct == 0) res |= 1 << (i - 1);
		if(ct == c[i]) res |= 1 << (i + tot - 1);
	} return res;
}

void FMT(int *f, int fl = 1) {
	rep(i, 0, tot * 2 - 1)
		rep(s, 0, U) if(s >> i & 1) {
		ll u = f[s ^ 1 << i], v = f[s];
		f[s] = (v + u * fl + mod) % mod;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, G = in, L = in; Q = in; if(L % G) { while(Q--) puts("0"); return 0; }
	L /= G; n /= G; getfac(L);
	rep(i, 1, n) {
		if(i * i > L) break; if(L % i) continue;
		++s[calc(i)]; if(i * i != L && L / i <= n) ++s[calc(L / i)];
	}
	U = (1 << (2 * tot)) - 1;
	rep(i, 0, U) if(s[i]) ++al, cnt[al] = s[i], stu[al] = i, ind[i] = al, vs[al] = qp(2, s[i]) - 1;
	f[0][0] = 1; g[al + 1][0] = 1;
	rep(i, 1, al) rep(s, 0, U) (f[i][s] += f[i - 1][s]) %= mod, (f[i][s | stu[i]] += 1ll * f[i - 1][s] * vs[i] % mod) %= mod;
	per(i, al, 1) rep(s, 0, U) (g[i][s] += g[i + 1][s]) %= mod, (g[i][s | stu[i]] += 1ll * g[i + 1][s] * vs[i] % mod) %= mod;
	rep(i, 0, al + 1) FMT(f[i]), FMT(g[i]);
	rep(i, 1, al) {
		rep(s, 0, U) h[i][s] = 1ll * f[i - 1][s] * g[i + 1][s] % mod;
		FMT(h[i], -1);
		rep(s, 0, U) if((s | stu[i]) == U) (ans[i] += h[i][s]) %= mod;
		ans[i] = 1ll * ans[i] * qp(2, cnt[i] - 1) % mod;
	}
	while(Q--) {
		int x = in; if(x % G || x / G > n || L % (x / G)) { puts("0"); continue; }
		printf("%d\n", ans[ind[calc(x / G)]]);
	}
	return 0;
}
