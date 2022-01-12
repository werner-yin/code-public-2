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

const int N = 510 + 10;

ll f[N][N];
int n, l, K, d[N], a[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, l = in, K = in;
	rep(i, 1, n) d[i] = in;
	rep(i, 1, n) a[i] = in;
	memset(f, 0x3f, sizeof f);
	f[1][0] = 0;
	d[n + 1] = l; 
	rep(i, 2, n + 1)
		rep(p, 1, i - 1)
		rep(j, 0, K)
		if(j + (i - p - 1) <= K) {
			chkmin(f[i][j + (i - p - 1)], f[p][j] + 1ll * a[p] * (d[i] - d[p]));
		}
	ll ans = 1e18;
	rep(i, 0, K) chkmin(ans, f[n + 1][i]);
	cout << ans << endl;
	return 0;
}
