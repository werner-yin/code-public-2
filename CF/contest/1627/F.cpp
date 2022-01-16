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
const int T = 510;
const int INF = 1e9;

int n, K;
int lu[T][T], lr[T][T], tot[T];
int dis[T][T];
int a[N], b[N], c[N], d[N];

void solve() {
	n = in, K = in;
	rep(i, 1, n) {
		a[i] = in, b[i] = in, c[i] = in, d[i] = in;
	}
	rep(i, 0, K + 1) rep(j, 0, K + 1) lu[i][j] = lr[i][j] = 0;
	rep(i, 1, n)
		if(a[i] == c[i]) 
			(b[i] > d[i]) && (swap(b[i], d[i]), 1), lr[a[i]][b[i]]++, lr[K - a[i] + 1][K - d[i] + 1]++;
		else 
			(a[i] > c[i]) && (swap(a[i], c[i]), 1), lu[c[i]][b[i]]++, lu[K - a[i] + 1][K - b[i] + 1]++;
	rep(i, 0, K + 1) rep(j, 0, K + 1) dis[i][j] = INF;
	dis[1][1] = 0; priority_queue < pair < int, pii >, vector < pair < int, pii > >, greater < pair < int, pii > > > q; q.ep(dis[1][1], pii(1, 1));
	while(q.size()) {
		auto v = q.top(); q.pop(); int d = v.fi, x, y; tie(x, y) = v.se;
		if(dis[x][y] != d) continue;
		if(x > 1 && dis[x][y] + lr[x - 1][y - 1] < dis[x - 1][y]) q.ep(dis[x - 1][y] = dis[x][y] + lr[x - 1][y - 1], pii(x - 1, y));
		if(x < K && dis[x][y] + lr[x][y - 1] < dis[x + 1][y]) q.ep(dis[x + 1][y] = dis[x][y] + lr[x][y - 1], pii(x + 1, y));
		if(y < K && dis[x][y] + lu[x][y] < dis[x][y + 1]) q.ep(dis[x][y + 1] = dis[x][y] + lu[x][y], pii(x, y + 1));
		if(y > 1 && dis[x][y] + lu[x][y - 1] < dis[x][y - 1]) q.ep(dis[x][y - 1] = dis[x][y] + lu[x][y - 1], pii(x, y - 1));
	}
	printf("%d\n", n - dis[K / 2 + 1][K / 2 + 1]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
