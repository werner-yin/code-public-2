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

const int N = 610;

int n, d1, d2;
int col[2][N][N];
veg G[N][N];

void solve(int col[N][N], int d) {
	rep(i, 1, n) rep(j, 1, n) G[i][j].clear();
	rep(x, 0, n)
		if(x * x <= d) {
			int y = sqrt(d - x * x);
			if(y * y != d - x * x) continue;
			rep(i, 1, n) rep(j, 1, n) {
				if(i + x <= n && j + y <= n) G[i][j].eb(i + x, j + y);
				if(i - x >= 1 && j - y >= 1) G[i][j].eb(i - x, j - y);
				if(i + x <= n && j - y >= 1) G[i][j].eb(i + x, j - y);
				if(i - x >= 1 && j + y <= n) G[i][j].eb(i - x, j + y);
			}
		} else break;
	function < void(int, int, int) > dfs = [&](int x, int y, int c) {
											   col[x][y] = c;
											   for(auto v : G[x][y])
												   if(!col[v.fi][v.se])
													   dfs(v.fi, v.se, 3 - c);
										   };
	rep(i, 1, n) rep(j, 1, n) if(!col[i][j]) dfs(i, j, 1);
}

int cnt[3][3];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in << 1, d1 = in, d2 = in;
	solve(col[0], d1); solve(col[1], d2);
	rep(i, 1, n) rep(j, 1, n) cnt[col[0][i][j]][col[1][i][j]]++;
	rep(i, 1, 2) rep(j, 1, 2) if(cnt[i][j] >= n * n / 4) {
		int cnt = 0;
		rep(x, 1, n) rep(y, 1, n) if(col[0][x][y] == i && col[1][x][y] == j) {
			printf("%d %d\n", x - 1, y - 1); ++cnt; if(cnt >= n * n / 4) return 0;
		} return 0;
	}
	return 0;
}
