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

int n, m, a[N], b[N], tot, cnt[N];
vec vcnt[N], pot;
set < pii > ban;

bool vail(int x, int y) { return ban.find({ x, y }) == ban.end() && ban.find({ y, x }) == ban.end(); }
/*
db slope(int x, int y) { return 1. * (cnt[y] - cnt[x]) / (b[y] - b[x]); }

void divide(int l, int r) {
	if(l == r) return; int mid = l + r >> 1;
	divide(l, mid); divide(mid + 1, r);
	top = 0;
	rep(i, mid + 1, r) {
		
	}
	
}
*/
void solve() {
	n = in, m = in; rep(i, 1, n) a[i] = b[i] = in;
	tot = n; sort(b + 1, b + n + 1); tot = unique(b + 1, b + n + 1) - b - 1;
	rep(i, 1, n) a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
	rep(i, 1, tot) cnt[i] = 0;
	rep(i, 1, n) ++cnt[a[i]];
	ban.clear(); 
	rep(i, 1, m) {
		int x = in, y = in;
		x = lower_bound(b + 1, b + tot + 1, x) - b, y = lower_bound(b + 1, b + tot + 1, y) - b;
		ban.ep(x, y);
	}
	/*rep(i, 1, tot) sort(G[i].begin(), G[i].end());
	top = 0;
	rep(i, 1, tot) {
		
		while(top > 1 && slope(stk[top - 1], stk[top]) < slope(stk[i], i)) top--;
		stk[++top] = i;
		}*/
	rep(i, 1, n) vcnt[i].clear();
	rep(i, 1, tot) vcnt[cnt[i]].eb(i);
	pot.clear();
	rep(i, 1, n) if(vcnt[i].size()) pot.eb(i), sort(vcnt[i].begin(), vcnt[i].end(), greater < int >());
	ll ans = 0;
	for(auto x : pot)
		for(auto y : pot) {
			priority_queue < tuple < int, int, int > > q;
			map < pii, bool > vis;
			auto add = [&](int u, int v) {
				if(vis[{ u, v }]) return;
				if(u >= vcnt[x].size()) return;
				if(v >= vcnt[y].size()) return;
				vis[{ u, v }] = true;
				q.ep(b[vcnt[x][u]] + b[vcnt[y][v]], u, v);
			};
			add(0, 0);
			while(q.size()) {
				auto t = q.top(); q.pop();
				int val, u, v; tie(val, u, v) = t;
				if(vcnt[x][u] != vcnt[y][v] && vail(vcnt[x][u], vcnt[y][v])) { chkmax(ans, 1ll * val * (x + y)); break; }
				add(u + 1, v); add(u, v + 1);
			}
		}
	printf("%lld\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
