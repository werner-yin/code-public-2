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

const int N = 260;
const int mod = 1e4 + 7;

int n, m;
int mat[N][N];

int det() {
	int res = 1;
	rep(i, 2, n) {
		int k = -1; rep(j, i, n) if(mat[j][i]) { k = j; break; }
		if(k == -1) return 0;
		if(k ^ i) swap(mat[i], mat[k]), res = mod - res;
		rep(j, i + 1, n)
			while(mat[j][i]) {
				int t = mat[j][i] / mat[i][i];
				rep(k, i, n) mat[j][k] = (mat[j][k] - mat[i][k] * t % mod + mod) % mod;
				if(mat[j][i]) swap(mat[j], mat[i]), res = mod - res;
			}
	} rep(i, 2, n) res = res * mat[i][i] % mod; return res;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 1, m) {
		int a = in, b = in;
		mat[a][a]++; mat[a][b]--;
	}
	rep(i, 1, n) rep(j, 1, n) mat[i][j] = (mat[i][j] % mod + mod) % mod;
	printf("%d\n", det());
	return 0;
}
