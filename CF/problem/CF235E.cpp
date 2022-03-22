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

const int N = 2e3 + 10;
const int mod = 1 << 30;

ll pA[N][N], pB[N][N];
bool pcd[N][N];
int mu[N], A, B, C, pri[N], pnum;
bool vis[N];

void init(int l) {
	rep(i, 2, l) {
		if(!vis[i]) pri[++pnum] = i, mu[i] = -1;
		rep(j, 1, pnum) {
			if(pri[j] * i > l) break; vis[pri[j] * i] = true;
			mu[pri[j] * i] = -mu[i]; if(i % pri[j] == 0) { mu[pri[j] * i] = 0; break; }
		}
	} mu[1] = 1;
	rep(i, 1, l) rep(j, 1, l) pcd[i][j] = __gcd(i, j) == 1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	A = in, B = in, C = in; init(max({ A, B, C }));
	rep(c, 1, C) rep(d, 1, A) rep(a, 1, A / d) (pA[c][d] += pcd[c][a * d] * (A / d / a) % mod) %= mod;
	rep(c, 1, C) rep(d, 1, B) rep(b, 1, B / d) (pB[c][d] += pcd[c][b * d] * (B / d / b) % mod) %= mod;
	ll ans = 0;
	rep(c, 1, C) {
		for(int d = 1; d <= min(A, B); d++) 
			(ans += mu[d] * pA[c][d] % mod * pB[c][d] % mod * (C / c) % mod + mod) %= mod;
	} printf("%lld\n", ans);
	return 0;
}
