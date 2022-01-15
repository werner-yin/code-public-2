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

const int N = 55 + 10;

int n, m, r, c;
char s[N][N];

void solve() {
	n = in, m = in, r = in, c = in;
	rep(i, 1, n) scanf("%s", s[i] + 1);
	int ans = 1000;
	rep(i, 1, n)
		rep(j, 1, m) {
		if(s[i][j] == 'B') {
			chkmin(ans, 2);
			if(j == c || i == r) chkmin(ans, 1);
			if(i == r && j == c) chkmin(ans, 0);
		}
	} if(ans == 1000) ans = -1;
	printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
