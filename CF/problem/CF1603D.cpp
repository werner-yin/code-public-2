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

ll f[19][N], sphi[N];
int n, K, pri[N], pnum, phi[N];
bool v[N];

void init(int l) {
	phi[1] = 1;
	rep(i, 2, l) {
		if(!v[i]) pri[++pnum] = i, phi[i] = i - 1;
		rep(j, 1, pnum) {
			if(pri[j] * i > l) break;
			v[pri[j] * i] = true; phi[pri[j] * i] = phi[i] * phi[pri[j]];
			if(i % pri[j] == 0) { phi[pri[j] * i] = phi[i] * pri[j]; break; }
		}
	} rep(i, 1, l) sphi[i] = sphi[i - 1] + phi[i];
}

ll calc(int l, int R) {
	ll res = 0; 
	for(int r; l <= R; l = r + 1) r = R / (R / l), res += sphi[R / l] * (r - l + 1);
	return res;
}

void solve(int l, int r, int xl, int xr, ll *g, ll *f) {
	if(l > r) return; int mid = l + r >> 1; ll res = calc(xr + 1, mid), mn = 1e18, pos = 0;
	per(i, xr, xl) {
		res += sphi[mid / i];
		if(res + g[i - 1] < mn) mn = res + g[i - 1], pos = i;
	} f[mid] = mn; 
	solve(l, mid - 1, xl, pos, g, f); solve(mid + 1, r, pos, xr, g, f);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = 100000; init(n);
	rep(i, 1, n) f[1][i] = 1ll * i * (i + 1) / 2;
	rep(k, 2, 17) solve(1, n, 1, n, f[k - 1], f[k]);
	int T = in;
	while(T--) {
		n = in, K = in;
		if(K >= 18 || (n < (1 << K))) printf("%d\n", n);
		else printf("%lld\n", f[K][n]);
	}
	return 0;
}
