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

int n, K;
char s[N];
int f[N][N][N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", s + 1); K = in; n = strlen(s + 1);
	rep(i, 1, n) f[i][i][0] = 1;
	rep(i, 1, n - 1) f[i][i + 1][0] = 1, f[i][i + 1][s[i] != s[i + 1]] = 2;
	for(int len = 3; len <= n; len++) {
		rep(l, 1, n - len + 1) {
			int r = l + len - 1;
			rep(k, 0, K) 
				f[l][r][k] = max(f[l + 1][r][k], f[l][r - 1][k]);
			rep(k, 0, K)
				chkmax(f[l][r][k + (s[l] != s[r])], f[l + 1][r - 1][k] + 2);
		}
	} int ans = 0; rep(i, 0, K) chkmax(ans, f[1][n][i]); cout << ans << endl; return 0;
}
