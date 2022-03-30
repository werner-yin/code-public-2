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

const int N = 2510;
const int mod = 998244353;

int n, ci, c[2], d[2];
int b[N], s[N], K, ban[N], f[N][N], g[N], h[N], sum[N], tsum[N];
vec imp[N];

void getf() {
	static int tmp[N][N], sf[N][N];
	f[0][0] = 1; int tot = 0;
	rep(x, 1, ci) {
		if(!imp[x].size()) continue; tot += sum[x]; 
		int lim1 = min(tot, c[0]), lim2 = min(tot, d[0]);
		rep(i, 0, lim1) rep(j, 0, lim2) tmp[i][j] = f[i][j], sf[i][j] = 0;
		//cerr << "C : " << sum[x] - tsum[x] << endl;
		for(auto v : imp[x]) {
			//cerr << "!" << v << " " << ban[v] << endl;
			per(i, lim1, 0) per(j, lim2, 0) { // blue.
				int cur = 0;
				if(ban[v] != 0 && i >= s[v] && j >= s[v]) cur = (cur + tmp[i - s[v]][j - s[v]]) % mod;
				if(ban[v] != 1 && i >= s[v]) cur = (cur + tmp[i - s[v]][j]) % mod;
				tmp[i][j] = cur; 
			}
		}
		rep(i, 0, lim1) rep(j, 0, lim2) (sf[i][j] += (i >= sum[x] - tsum[x] ? tmp[i - (sum[x] - tsum[x])][j] : 0)) %= mod;
		rep(i, 0, lim1) rep(j, 0, lim2) tmp[i][j] = f[i][j];
		for(auto v : imp[x]) {
			per(i, lim1, 0) per(j, lim2, 0) { // red.
				int cur = 0;
				if(ban[v] != 2 && j >= s[v]) cur = (cur + tmp[i][j - s[v]]) % mod;
				if(ban[v] != 3) cur = (cur + tmp[i][j]) % mod;
				tmp[i][j] = cur; 
			}
		} rep(i, 0, lim1) rep(j, 0, lim2) (sf[i][j] += tmp[i][j]) %= mod;
		rep(i, 0, lim1) rep(j, 0, lim2) f[i][j] = sf[i][j];
	} //cerr << "F: " << endl; rep(i, 0, c[0]) { rep(j, 0, d[0]) cerr << f[i][j] << " "; cerr << endl; } cerr << endl;
}

void getg() {
	g[0] = 1; int tot = 0;
	rep(x, 1, ci) if(!tsum[x]) {
		tot += sum[x]; int lim = min(tot, c[0]), num = sum[x];
		if(!num) continue; per(i, lim, 0) g[i] = ((i >= num ? g[i - num] : 0) + g[i]) % mod;
	}
}

void geth() {
	h[0] = 1; int tot = 0;
	rep(x, 1, n) if(!~ban[x]) {
		tot += s[x]; int lim = min(tot, d[0]);
		per(i, lim, 0) h[i] = ((i >= s[x] ? h[i - s[x]] : 0) + h[i]) % mod;
	}
}

void solve() {
	n = in, ci = in; rep(i, 0, 1) c[i] = in; rep(i, 0, 1) d[i] = in;
	rep(i, 1, ci) imp[i].clear(), sum[i] = tsum[i] = 0; rep(i, 1, n) b[i] = in, s[i] = in, sum[b[i]] += s[i], ban[i] = -1; 
	K = in; rep(i, 1, K) { int x = in; ban[x] = in; imp[b[x]].eb(x); tsum[b[x]] += s[x]; }
	memset(f, 0, sizeof f); memset(g, 0, sizeof g); memset(h, 0, sizeof h);
	getf(); getg(); geth(); int al = 0; rep(i, 1, n) al += s[i];
	rep(i, 1, min(al, c[0])) g[i] = (g[i] + g[i - 1]) % mod;//, cerr << g[i] << " "; cerr << endl;
	rep(i, 1, min(al, d[0])) h[i] = (h[i] + h[i - 1]) % mod;//, cerr << h[i] << " "; cerr << endl;
	int ans = 0;
	rep(i, 0, c[0])
		rep(j, 0, d[0]) if(f[i][j]) {
		int lc = max(al - i - c[1], 0), rc = c[0] - i;
		int ld = max(al - j - d[1], 0), rd = d[0] - j;
		//cerr << "!" << i << " " << j << " " << lc << " " << rc << " " << ld << " " << rd << endl;
		if(lc > rc || ld > rd) continue;
		ans = (ans + 1ll * f[i][j] * (g[rc] - (lc ? g[lc - 1] : 0) + mod) % mod * (h[rd] - (ld ? h[ld - 1] : 0) + mod) % mod) % mod;
	} printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
