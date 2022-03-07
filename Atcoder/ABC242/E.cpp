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
const int mod = 998244353;

char s[N];
int f[N][2][2], n;

int rev(int x) { return n - x + 1; }
void solve() {
	n = in; scanf("%s", s + 1); 
	memset(f[0], 0, sizeof f[0]); f[0][0][0] = 1;
	rep(i, 1, (n + 1) / 2) {
		memset(f[i], 0, sizeof f[i]);
		rep(j, 0, 1) rep(k, 0, 1) if(f[i - 1][j][k]) 
			rep(c, 'A', (j == 1 ? 'Z' : s[i])) {
				(f[i][j | (c < s[i])][c < s[rev(i)] ? 0 : c > s[rev(i)] ? 1 : k] += f[i - 1][j][k]) %= mod;
			}
	}
	int ans = 0;
	rep(j, 0, 1) rep(k, 0, 1) {
		if(j == 0 && k == 1) continue;
		(ans += f[n + 1 >> 1][j][k]) %= mod;
	}
	printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
