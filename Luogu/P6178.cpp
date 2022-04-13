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

const int N = 310;
const int mod = 1e9 + 7;

int n, m, tp;
ll mat[N][N];

int det() {
	int ans = 1; 
	rep(i, 2, n) {
		int p = -1; rep(j, i, n) if(mat[j][i]) { p = j; break; }
		if(p == -1) return 0; if(p ^ i) ans = mod - ans, swap(mat[p], mat[i]);
		rep(j, i + 1, n) while(mat[j][i]) {
			int t = mat[j][i] / mat[i][i];
			rep(k, i, n) mat[j][k] = ((mat[j][k] - 1ll * mat[i][k] * t % mod) % mod + mod) % mod;
			if(!mat[j][i]) continue;
			ans = mod - ans; swap(mat[j], mat[i]);
		}
	} rep(i, 2, n) ans = 1ll * ans * mat[i][i] % mod; return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, tp = in;
	rep(i, 1, m) {
		int u = in, v = in, w = in;
		if(tp == 0) mat[u][u] += w, mat[v][v] += w, mat[u][v] -= w, mat[v][u] -= w;
		else mat[v][v] += w, mat[u][v] -= w;
	}
	rep(i, 1, n) rep(j, 1, n) mat[i][j] = (mat[i][j] % mod + mod) % mod;
	printf("%d\n", det()); return 0;
}
