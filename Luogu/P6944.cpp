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

const int N = 510;

db f[N][N], g[N][N], C[N][N];
int n, d, r;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, d = in, r = in;
	rep(i, 0, n) {
		C[i][0] = 1;
		rep(j, 1, i) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	f[0][n] = 1;
	rep(i, 0, d - 1)
		rep(j, 0, n)
		rep(k, 0, j) {
			f[i + k][k] += f[i][j] * C[j][k];
			g[i + k][k] += (g[i][j] + min(r, k) * f[i][j]) * C[j][k];
		}
	db ans1 = 0, ans2 = 0;
	rep(i, 0, n) ans1 += f[d][i], ans2 += g[d][i];
	printf("%.7lf\n", ans2 / ans1 + r);
	return 0;
}
