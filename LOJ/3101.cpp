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

const int N = 5e4 + 10;
const int M = 1e5 + 10;
const int B = 1e4 + 10;

int T, n, m, ans[N], t[M], x[M], y[M], tot, op[M], l, r, alive[N], die[N];
set < int > imp[N];
map < int, int > id[N][2];
vec G[N + M << 1];
bitset < B + 2 > cango[N + M << 1];
bitset < N + M << 1 > vis;
bitset < N > mustdie;
int ind[N + M << 1];

void dfs(int x) {
	if(vis.test(x)) return;
	vis.set(x); cango[x].reset(); if(ind[x] >= l && ind[x] <= r) cango[x].set(ind[x] - l); for(auto y : G[x]) dfs(y), cango[x] |= cango[y];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	T = in, n = in, m = in;
	rep(i, 1, m) op[i] = in, t[i] = in, x[i] = in, y[i] = in, imp[x[i]].ep(t[i]);
	rep(i, 1, n) imp[i].ep(T + 1);
	auto DD = [](int x, int t) { auto it = id[x][0].lower_bound(t); return it->se; };
	auto AA = [](int x, int t) { auto it = id[x][1].lower_bound(t); return it->se; };
	rep(i, 1, n) {
		for(auto v : imp[i]) id[i][0][v] = ++tot, id[i][1][v] = ++tot;
		for(auto it = imp[i].begin(); it != imp[i].end(); it++) {
			if(next(it) != imp[i].end()) G[id[i][0][*it]].eb(id[i][0][*next(it)]);
			if(it != imp[i].begin()) G[id[i][1][*it]].eb(id[i][1][*prev(it)]);
		}
	} rep(i, 1, n) alive[i] = AA(i, T + 1), ind[die[i] = DD(i, T + 1)] = i;
	rep(i, 1, m) {
		if(op[i] == 0) {
			G[DD(x[i], t[i])].eb(DD(y[i], t[i] + 1));
			G[AA(y[i], t[i] + 1)].eb(AA(x[i], t[i]));
		} else {
			G[AA(x[i], t[i])].eb(DD(y[i], t[i]));
			G[AA(y[i], t[i])].eb(DD(x[i], t[i]));
		}
	}
	for(l = 1; l <= n; l += B) {
		r = min(n, l + B - 1); vis.reset();
		rep(i, 1, n) dfs(alive[i]); bitset < B + 2 > nowdie;
		rep(i, l, r) if(cango[alive[i]][i - l]) nowdie.set(i - l), mustdie.set(i);
		rep(i, 1, n) ans[i] += r - l + 1 - (cango[alive[i]] | nowdie).count();
	} rep(i, 1, n) printf("%d%c", mustdie[i] ? 0 : ans[i] - 1, " \n"[i == n]); return 0;
}
