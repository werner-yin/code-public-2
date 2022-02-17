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

const int N = 5e5 + 10;

vec G[N];
int val[N], siz[N], son[N], ans[N], n, dep[N];
int mxv[1 << 22], tag;

void dfs(int x, int p) {
	siz[x] = 1; dep[x] = dep[p] + 1;
	for(auto y : G[x]) dfs(y, x), son[x] = siz[y] > siz[son[x]] ? y : son[x], siz[x] += siz[y];
}

void query(int x, int res, int &ans, int tdep) {
	chkmax(ans, mxv[res ^ tag] + dep[x] - tdep * 2);
	rep(i, 0, 21) chkmax(ans, mxv[res ^ tag ^ (1 << i)] + dep[x] - tdep * 2);
	for(auto y : G[x]) 
		query(y, res ^ 1 << val[y], ans, tdep);
}

void add(int x, int res, int tdep) {
	for(auto y : G[x]) add(y, res ^ 1 << val[y], tdep);
	chkmax(mxv[res ^ tag], dep[x]);
}

void remove(int x, int res) {
	for(auto y : G[x]) remove(y, res ^ 1 << val[y]);
	mxv[res ^ tag] = -1e9;
}

void tdfs(int x, int fl) {
	for(auto y : G[x]) if(y ^ son[x]) tdfs(y, 0), chkmax(ans[x], ans[y]);
	if(son[x]) tdfs(son[x], 1), chkmax(ans[x], ans[son[x]]);
	tag ^= 1 << val[son[x]]; chkmax(ans[x], mxv[tag] - dep[x]); rep(i, 0, 21) chkmax(ans[x], mxv[tag ^ (1 << i)] - dep[x]);
	chkmax(mxv[tag], dep[x]);
	for(auto y : G[x]) if(y ^ son[x]) query(y, 1 << val[y], ans[x], dep[x]), add(y, 1 << val[y], dep[x]);
	if(fl == 0) remove(x, 0), tag = 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { G[in].eb(i); char t = getchar(); while(!isalpha(t)) t = getchar(); val[i] = t - 'a'; }
	memset(mxv, 0xcf, sizeof mxv);
	dfs(1, 0); tdfs(1, 1); rep(i, 1, n) printf("%d ", ans[i]); puts("");
	return 0;
}
