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

#define OK return puts("YES"), void()
#define GG return puts("NO"), void()

const int N = 1010;
const pii H[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

int n, a[N][N], b[N][N];

void solve() {
	int ans = 0; n = in; rep(i, 1, n) rep(j, 1, n) a[i][j] = in;
	rep(i, 0, n + 1) rep(j, 0, n + 1) b[i][j] = 0;
	rep(i, 1, n) rep(j, 1, n) {
		if(b[i - 1][j] == 0) {
			ans ^= a[i][j];
			for(auto v : H) b[i + v.fi][j + v.se] ^= 1;
		}
	} printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
