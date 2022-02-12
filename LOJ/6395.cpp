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

const int N = 3010;
const int mod = 59393;

int n, K, a[N], f[N * 12][N << 1], deg[N], s[N], tot;
veg al;
pii pre[N * 12][N << 1];

int calc(int x) {
	ll res = 0; per(i, K, 0) res = (res * x + a[i]) % mod;
	return res;
}

void tcalc(int *f, int *g, pii *pre, int vt) {
	int v = calc(vt + 1);
	rep(i, 0, n - 2) {
		f[i] = g[i]; pre[i] = { -1, 0 };
		if(i >= vt) 
			if(f[i - vt] + v >= f[i]) f[i] = f[i - vt] + v, pre[i] = { 0, vt };
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; rep(i, 0, K) a[i] = in;
	memset(f, 0xcf, sizeof f); f[0][0] = 0;
	rep(i, 1, n - 2) 
		tcalc(f[i], f[i - 1], pre[i], i);
	int cx = n - 2, cy = n - 2;
	while(cx != 0 || cy != 0) {
		if(pre[cx][cy].fi == 0) {
			deg[++tot] = cx;
			cy -= pre[cx][cy].se;
		} else cx--;
	}
	assert(tot <= n);
	rep(i, 1, n) deg[i]++;
	set < pii > q;
	printf("%d %d\n", n - 1, f[n - 2][n - 2]);
	rep(i, 1, n) q.ep(deg[i], i);
	rep(i, 1, n - 1) {
		auto x = *q.rbegin(); q.erase(--q.end());
		auto y = *q.rbegin(); q.erase(--q.end());
		printf("%d %d\n", x.se, y.se);
		x.fi--; y.fi--; if(x.fi) q.ep(x); if(y.fi) q.ep(y);
	}
	return 0;
}
