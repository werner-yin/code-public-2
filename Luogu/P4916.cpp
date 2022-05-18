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

const int N = 1e5 + 10;
const int mod = 998244353;

int phi[N], pri[N], n, m, K, fac[N << 1], ifac[N << 1], pnum;
bool vis[N];

void shai(int l) {
	rep(i, 2, l) {
		if(!vis[i]) pri[++pnum] = i, phi[i] = i - 1; 
		rep(j, 1, pnum) {
			int t = pri[j] * i; if(t > l) break;
			vis[t] = true; phi[t] = phi[pri[j]] * phi[i];
			if(i % pri[j] == 0) { phi[t] = pri[j] * phi[i]; break; }
		}
	} phi[1] = 1;
}

ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }
ll C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : 1ll * fac[x] * ifac[y] % mod * ifac[x - y] % mod; }
void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = 1ll * fac[i - 1] * i % mod; ifac[l] = qp(fac[l], mod - 2);
	per(i, l - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
}

ll g(int n, int m) {
	ll ret = 0;
	rep(x, 0, m) {
		int lef = m - x * (K + 1); if(lef < 0) break;
		ret = (ret + 1ll * (x & 1 ? mod - 1 : 1) * C(n, x) % mod * C(lef + n - 1, n - 1) % mod) % mod;
	} return ret;
}

ll f(int n, int m) {
	if(m <= K) return C(n, m);
	if(n == m + 1) return 0;
	ll ret = 0;
	rep(i, 0, K)
		(ret += g(n - m - 1, m - i) * (i + 1) % mod) %= mod;
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, K = in;
	if(n == m) return puts(n <= K ? "1" : "0");
	shai(n); init(n * 2); ll ret = 0;
	rep(d, 1, n) if(n % d == 0 && m % (n / d) == 0) ret = (ret + f(d, m / (n / d)) * phi[n / d] % mod) % mod;
	(ret *= qp(n)) %= mod; cout << ret << endl; return 0;
}
