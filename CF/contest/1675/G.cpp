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

const int N = 250 + 10;
const int inf = 0x3f3f3f3f;

int n, a[N], m, f[N][N][N], ps[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, n) a[i] = in, ps[i] = ps[i - 1] + a[i];
	memset(f, 0x3f, sizeof f);
	f[1][m][m] = 0;
	rep(i, 1, n - 1) {
		per(j, m, 0)
			per(lst, m, 0) if(f[i][j][lst] < inf) {
			chkmin(f[i][j - 1][lst - 1], f[i][j][lst]);
			f[i][j][lst] += abs(ps[i] - j);
			int mxv = min(m - j, lst);
			chkmin(f[i + 1][j + mxv][mxv], f[i][j][lst]);
		}
	} int ans = inf;
	rep(j, 0, m) chkmin(ans, f[n][m][j]);
	cout << ans << endl;
	return 0;
}
