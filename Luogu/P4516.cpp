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

const int N = 1e5 + 10;
const int mod = 1e9 + 7;

int f[N][110][2][2], n, K, siz[N], tmp[N][2][2];
vec G[N];

void upd(int &x) { x = x + (x >> 31 & mod); }

void dfs(int x, int p) {
	f[x][0][0][0] = f[x][1][0][1] = siz[x] = 1;
	for(auto y : G[x]) if(y ^ p) {
			dfs(y, x);
			rep(i, 0, min(siz[x] + siz[y], K)) tmp[i][0][0] = tmp[i][0][1] = tmp[i][1][0] = tmp[i][1][1] = 0;
			rep(i, 0, min(siz[x], K)) rep(a, 0, 1) rep(b, 0, 1) if(f[x][a][b])
				rep(j, 0, min(K - i, siz[y])) rep(u, !b, 1) rep(v, 0, 1) if(f[y][u][v]) {
					upd(tmp[i + j][a | v][b] += 1ll * f[x][i][a][b] * f[y][j][u][v] % mod - mod);
				}
			rep(i, 0, min(siz[x] + siz[y], K)) rep(a, 0, 1) rep(b, 0, 1) f[x][i][a][b] = tmp[i][a][b];
			siz[x] += siz[y];
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v); G[v].eb(u); }
	dfs(1, 0); printf("%d\n", (f[1][K][1][0] + f[1][K][1][1]) % mod);
	return 0;
}
