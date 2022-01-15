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

const int N = 1e5 + 10;
const ll INF = 1e18;

map < int, ll > dis[N];
map < int, vector < tuple < int, int, int > > > G[N];
int n, m, K;
int x[N];

void solve() {
	n = in, m = in, K = in;
	rep(i, 1, n) map < int, vector < tuple < int, int, int > > >().swap(G[i]),
		map < int, ll >().swap(dis[i]);
	rep(i, 1, n) x[i] = in;
	rep(i, 1, K) {
		int a = in, b = in, c = in, d = in, h = in;
		dis[a][b] = dis[c][d] = INF;
		G[a][b].eb(c, d, h);
	} dis[n][m] = INF;
	dis[1][1] = 0;
	rep(i, 1, n) {
		ll mn = INF;
		vec pot; for(const auto &v : dis[i]) pot.eb(v.fi);
		for(const auto &v : pot)  {
			chkmin(dis[i][v], mn + 1ll * v * x[i]);
			chkmin(mn, -1ll * v * x[i] + dis[i][v]);
		} mn = INF;
		per(j, int(pot.size()) - 1, 0) {
			int v = pot[j];
			chkmin(dis[i][v], mn - 1ll * v * x[i]);
			chkmin(mn, 1ll * v * x[i] + dis[i][v]);
		}
		for(auto v : pot) {
			if(G[i].count(v)) {
				for(auto y : G[i][v]) {
					int c, d, h; tie(c, d, h) = y;
					chkmin(dis[c][d], dis[i][v] - h);
				}
			}
		}
	} if(dis[n][m] <= 1e17) printf("%lld\n", dis[n][m]);
	else puts("NO ESCAPE");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
