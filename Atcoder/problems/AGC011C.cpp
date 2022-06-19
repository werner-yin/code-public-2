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

int n, m;
vec G[N], P[N];
int fa[N];

int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }

bool fl;
int col[N];

void dfs(int x, int c) {
	if(!fl) return;
	col[x] = c;
	for(auto y : G[x]) if(!col[y]) dfs(y, c ^ 1); else fl &= c != col[y];
	for(auto y : P[x]) if(!col[y]) dfs(y, c ^ 1); else fl &= c != col[y];
}

bool check(int x) { fl = 1; dfs(x, 2); return fl; }

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, m) { int u = in, v = in; G[u].eb(v), P[v].eb(u); }
	rep(i, 1, n) fa[i] = i;
	rep(i, 1, n) {
		int lst = 0;
		for(auto v : P[i]) {
			if(lst) fa[gf(lst)] = gf(v);
			lst = v;
		}
		for(auto v : G[i]) {
			if(lst) fa[gf(lst)] = gf(v);
			lst = v;
		}
	}
	int tot1 = 0, tot2 = 0, tot3 = 0; ll ans = 0;
	rep(i, 1, n) tot1 += gf(i) == i;
	//cerr << tot1 << endl;
	rep(i, 1, n) tot2 += !G[i].size() && !P[i].size();
	//cerr << tot2 << endl;
	rep(i, 1, n) fa[i] = i; rep(i, 1, n) for(auto j : G[i]) fa[gf(i)] = gf(j);
	rep(i, 1, n) tot3 += gf(i) == i;
	//cerr << tot3 << endl;
	rep(i, 1, n) {
		if(!P[i].size() && !G[i].size()) ans += n;
		else if(!P[i].size()) ans += (check(i) ? tot1 : tot3);
		else ans += tot2;
	}
	cout << ans << endl;
	return 0;
}
