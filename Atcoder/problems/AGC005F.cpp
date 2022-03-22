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

const int N = 2e5 + 10;
const int mod = 924844033;

int n, siz[N], fac[N], ifac[N], cnt[N];
vec G[N];

void dfs(int x, int p) { siz[x] = 1; for(auto y : G[x]) if(y ^ p) dfs(y, x), siz[x] += siz[y]; }
ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

int Wn[N << 2], A[N << 2], B[N << 2], rev[N << 2], len;

void init_NTT(int l) {
	for(len = 1; len <= l * 2; len <<= 1);
	rep(i, 1, len - 1) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
	for(int h = 1; h <= len; h <<= 1) Wn[h] = qp(5, (mod - 1) / h);
}

void NTT(int *f, int fl = 1) {
	rep(i, 1, len - 1) if(i < rev[i]) swap(f[i], f[rev[i]]);
	for(int h = 2; h <= len; h <<= 1) {
		ll wn = Wn[h];
		for(int i = 0, j = h >> 1; i < len; i += h) {
			ll ww = 1;
			for(int k = i; k < i + j; k++) {
				ll u = f[k], v = f[k + j] * ww % mod; ww = ww * wn % mod;
				f[k] = (u + v) % mod, f[k + j] = (u - v + mod) % mod;
			}
		}
	}
	if(fl == -1) { reverse(f + 1, f + len); ll invv = qp(len); rep(i, 0, len - 1) f[i] = f[i] * invv % mod; }
}

int C[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	dfs(1, 0); rep(i, 2, n) ++cnt[siz[i]], ++cnt[n - siz[i]];
	fac[0] = 1; rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod; ifac[n] = qp(fac[n]);
	per(i, n - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
	init_NTT(n + 1); rep(i, 0, n) A[i] = 1ll * cnt[i] * fac[i] % mod, B[i] = ifac[i];
	reverse(A + 1, A + n + 1); 
	NTT(A); NTT(B); rep(i, 0, len) A[i] = 1ll * A[i] * B[i] % mod; NTT(A, -1);
	reverse(A + 1, A + n + 1);
	rep(i, 1, n) A[i] = 1ll * A[i] * ifac[i] % mod;
	
	//rep(i, 0, n) rep(j, 0, n) (C[i + j] += 1ll * A[i] * B[j] % mod) %= mod;
	//reverse(C + 1, C + n + 1);
	//rep(i, 0, n) A[i] = 1ll * C[i] * ifac[i] % mod;
	//auto binom = [](int x, int y) { return x < y || x < 0 || y < 0 ? 0 : 1ll * fac[x] * ifac[y] % mod * ifac[x - y] % mod; };
	//rep(i, 2, n) {
	//	rep(x, 1, n)
	//		cerr << siz[i] << " " << x << " " << binom(n, x) - binom(siz[i], x) - binom(n - siz[i], x) << endl,
	//		A[x] += binom(siz[i], x) + binom(n - siz[i], x);
	//}
	//rep(i, 1, n) A[i] = (-A[i] + binom(n, i) * n) % mod;
	rep(i, 1, n) A[i] = (mod - A[i] + 1ll * fac[n] * ifac[i] % mod * ifac[n - i] % mod * n % mod) % mod;
	rep(i, 1, n) printf("%d\n", A[i]); return 0;
}
