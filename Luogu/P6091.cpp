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

int n, d, t;

ll qp(ll x, int t, int mod) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }
int phi(int x) {
	int res = x;
	rep(i, 2, x) {
		if(i * i > x) break; if(x % i) continue;
		res = res / i * (i - 1); while(x % i == 0) x /= i;
	} if(x > 1) res = res / x * (x - 1); return res;
}
int fac[N], tot;

void factor(int x) {
	tot = 0;
	rep(i, 2, t) {
		if(i * i > x) break; if(x % i) continue;
		fac[++tot] = i; while(x % i == 0) x /= i;
	} if(x > 1) fac[++tot] = x;
}

bool check(int x) { rep(i, 1, tot) if(qp(x, t / fac[i], n) == 1) return false; return true; }

void solve() {
	n = in, d = in, t = phi(n);
	factor(t); int g = -1; 
	rep(i, 1, 300) if(__gcd(i, n) == 1 && check(i)) { g = i; break; }
	vec pot; if(~g) rep(i, 1, t) if(__gcd(i, t) == 1) pot.eb(qp(g, i, n));
	printf("%ld\n", pot.size()); sort(pot.begin(), pot.end());
	int ctt = d; for(auto v : pot) { if(ctt == 1) printf("%d ", v), ctt = d + 1; ctt--; }
	puts("");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
