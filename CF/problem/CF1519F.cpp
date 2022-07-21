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

int n, m, a[N], b[N], lef[N], c[20][20];
int f[15][20000];
int ret[N];

int encode() {
	int res = 0; rep(j, 1, m) res = res * (b[j] + 1) + ret[j];
	return res;
}

void decode(int s) { per(j, m, 1) ret[j] = s % (b[j] + 1), s /= b[j] + 1; }

void dfs(int i, int pos, int lef, int val) {
	if(pos == m + 1) {
		if(lef) return; int t = encode(); chkmin(f[i + 1][t], val); return;
	}
	rep(j, 0, min(ret[pos], lef)) {
		ret[pos] -= j;
		dfs(i, pos + 1, lef - j, val + (j != 0) * c[i + 1][pos]);
		ret[pos] += j;
	}
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, n) a[i] = in; rep(i, 1, m) b[i] = in;
	rep(i, 1, n) rep(j, 1, m) c[i][j] = in;
	rep(i, lef[0] = 1, m) lef[i] = lef[i - 1] * (b[i] + 1);
	memset(f, 0x3f, sizeof f); rep(j, 1, m) ret[j] = b[j]; f[0][encode()] = 0;
	rep(i, 0, n - 1) rep(j, 0, lef[m] - 1) if(f[i][j] < 1e9) {
		decode(j); dfs(i, 1, a[i + 1], f[i][j]);
	} int ret = 1e9 + 7; rep(j, 0, lef[m] - 1) chkmin(ret, f[n][j]); if(ret > 1e9) ret = -1; cout << ret << endl;
	return 0;
}
