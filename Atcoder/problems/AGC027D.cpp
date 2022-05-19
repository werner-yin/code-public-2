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

/* prime, mu, phi */
int mu[N], phi[N], pnum, pri[N];
bool v[N];

void shai(int l) {
	mu[1] = phi[1] = 1;
	rep(i, 2, l) {
		if(!v[i]) pri[++pnum] = i, mu[i] = -1, phi[i] = i - 1;
		rep(j, 1, pnum) {
			int t = i * pri[j]; if(t > l) break; v[t] = 1; 
			if(i % pri[j] == 0) { mu[t] = 0, phi[t] = phi[i] * pri[j]; break; }
			phi[t] = phi[i] * phi[pri[j]], mu[t] = -mu[i];
		}
	} 
}

int n;
ll a[1010][1010];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; shai(10000);
	if(n == 2) return puts("4 7\n23 10"), 0;
	rep(i, 1, n) rep(j, i & 1 ? 1 : 2, n) 
		a[i][j] = 1ll * pri[i + j >> 1] * pri[n + (i - j + n + 1 >> 1)], j++;
	auto lcm = [&](ll x, ll y) { return x == 0 || y == 0 ? x | y : x / __gcd(x, y) * y; };
	rep(i, 1, n) rep(j, 1, n) if(i + j & 1) a[i][j] = lcm(lcm(a[i - 1][j], a[i + 1][j]), lcm(a[i][j - 1], a[i][j + 1])) + 1;
	rep(i, 1, n) rep(j, 1, n) printf("%lld%c", a[i][j], " \n"[j == n]); 
	return 0;
}
