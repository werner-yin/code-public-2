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

ll f[N][2], ans = 1e18;
int n, a[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i ,1, n) a[i] = in;
	memset(f, 0x3f, sizeof f);
	f[2][1] = a[1];
	rep(i, 2, n)
		rep(j, 0, 1)
		if(f[i][j] < 1e18) {
			if(j) chkmin(f[i + 1][0], f[i][j]);
			chkmin(f[i + 1][1], f[i][j] + a[i]);
		}
	chkmin(ans, f[n + 1][0]); chkmin(ans, f[n + 1][1]);
	memset(f, 0x3f, sizeof f);
	f[2][0] = 0;
	rep(i, 2, n - 1)
		rep(j, 0, 1)
		if(f[i][j] < 1e18) {
			if(j) chkmin(f[i + 1][0], f[i][j]);
			chkmin(f[i + 1][1], f[i][j] + a[i]);
		}
	chkmin(ans, f[n][0] + a[n]); chkmin(ans, f[n][1] + a[n]);
	cout << ans << endl;
	return 0;
}
