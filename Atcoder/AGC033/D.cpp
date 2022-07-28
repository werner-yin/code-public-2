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

const int N = 190;

char a[N][N];
int s[2][N][N], h, w;
int f[2][N][N][N], g[2][N][N][N];

int get(int c, int x1, int y1, int x2, int y2) { return s[c][x2][y2] + s[c][x1 - 1][y1 - 1] - s[c][x1 - 1][y2] - s[c][x2][y1 - 1]; }
bool check(int x1, int y1, int x2, int y2) { return get(0, x1, y1, x2, y2) == 0 || get(1, x1, y1, x2, y2) == 0; }

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	h = in, w = in;
	rep(i, 1, h) scanf("%s", a[i] + 1);
	rep(i, 1, h) rep(j, 1, w) s[0][i][j] = a[i][j] == '.';
	rep(i, 1, h) rep(j, 1, w) s[1][i][j] = a[i][j] == '#';
	rep(_, 0, 1)
		rep(i, 1, h) rep(j, 1, w)
		s[_][i][j] += s[_][i - 1][j] + s[_][i][j - 1] - s[_][i - 1][j - 1];
	rep(i, 1, h) {
		rep(j, i, h) {
			int p = 0;
			rep(k, 1, w) {
				chkmax(p, k - 1);
				while(p < w && check(i, k, j, p + 1)) p++;
				f[0][i][j][k] = p;
			}
		}
	}
	rep(i, 1, w) {
		rep(j, i, w) {
			int p = 0;
			rep(k, 1, h) {
				chkmax(p, k - 1);
				while(p < h && check(k, i, p + 1, j)) p++;
				g[0][i][j][k] = p;
			}
		}
	}
	if(f[0][1][h][1] >= w || g[0][1][w][1] >= h) return cout << 0 << endl, 0;
	int o = 0;
	rep(d, 1, 30) {
		rep(i, 1, h) rep(j, i, h) {
			int p = 0;
			rep(k, 1, w) {
				chkmax(p, k - 1);
				f[o ^ 1][i][j][k] = f[o][i][j][k];
				chkmax(f[o ^ 1][i][j][k], f[o][i][j][f[o][i][j][k] + 1]);
				while(p < w && (g[o][k][p + 1][i] >= j || g[o][k][p + 1][g[o][k][p + 1][i] + 1] >= j))
					p++;
				chkmax(f[o ^ 1][i][j][k], p);
			}
		}
		rep(i, 1, w) rep(j, i, w) {
			int p = 0;
			rep(k, 1, h) {
				chkmax(p, k - 1);
				g[o ^ 1][i][j][k] = g[o][i][j][k];
				chkmax(g[o ^ 1][i][j][k], g[o][i][j][g[o][i][j][k] + 1]);
				while(p < h && (f[o][k][p + 1][i] >= j || f[o][k][p + 1][f[o][k][p + 1][i] + 1] >= j))
					p++;
				chkmax(g[o ^ 1][i][j][k], p);
			}
		} if(f[o ^ 1][1][h][1] >= w || g[o ^ 1][1][w][1] >= h) return cout << d << endl, 0;
		o ^= 1;
	} assert(0);
	return 0;
}
