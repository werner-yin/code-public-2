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
const int LIM = 400;

int n, q, ed[N];

char s[N];

namespace ACAM {
	int ndn = 1, ch[N][27], fail[N], tim, dfn[N], R[N], fa[N], dep[N];
	vec G[N];
	void dfs(int x, int p) { dfn[x] = ++tim; for(auto y : G[x]) dfs(y, x); R[x] = tim; }
	void build() {
		queue < int > q; rep(i, 0, 25) ch[0][i] = 1; q.ep(1);
		while(q.size()) {
			int x = q.front(), F = fail[x]; q.pop(); G[F].eb(x);
			rep(i, 0, 25)
				if(!ch[x][i]) ch[x][i] = ch[F][i];
				else fail[ch[x][i]] = ch[F][i], q.ep(ch[x][i]);
		} dfs(1, 0);
	}
	int insert() {
		scanf("%s", s + 1); int l = strlen(s + 1), p = 1;
		rep(i, 1, l) {
			int x = s[i] - 'a', &v = ch[p][x];
			if(!v) v = ++ndn, dep[v] = dep[p] + 1, fa[v] = p; p = v;
		} return p;
	}
}

using ACAM :: fa;
using ACAM :: dfn;
using ACAM :: R;
using ACAM :: dep;
using ACAM :: ndn;

struct {
	ll tr[N];
	void add(int x, int v) { for(; x <= ndn; x += x & -x) tr[x] += v; }
	ll query(int x) { ll res = 0; for(; x; x -= x & -x) res += tr[x]; return res; }
	ll query(int l, int r) { return l <= r ? query(r) - query(l - 1) : 0; }
	void add(int l, int r, int v) { if(l > r) return; add(l, v); add(r + 1, -v); }
} T;

int tot, id[N];
ll pv[N / LIM + 10][N];
ll ans[N];
veg G[N], GR[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, q = in; rep(i, 1, n) ed[i] = ACAM :: insert();
	ACAM :: build();
	rep(i, 1, n) if(dep[ed[i]] >= LIM) {
		id[i] = ++tot;
		for(int x = ed[i]; x; x = fa[x]) T.add(dfn[x], 1);
		rep(j, 1, n) pv[tot][j] = pv[tot][j - 1] + T.query(dfn[ed[j]], R[ed[j]]);
		for(int x = ed[i]; x; x = fa[x]) T.add(dfn[x], -1);
	}
	rep(i, 1, q) {
		int l = in, r = in, k = in;
		if(dep[ed[k]] >= LIM) ans[i] = pv[id[k]][r] - pv[id[k]][l - 1];
		else G[r].eb(i, k), GR[l - 1].eb(i, k);
	}
	rep(i, 1, n) {
		T.add(dfn[ed[i]], R[ed[i]], 1);
		for(auto v : G[i]) {
			int id = v.fi, x = ed[v.se];
			while(x) ans[id] += T.query(dfn[x]), x = fa[x];
		}
		for(auto v : GR[i]) {
			int id = v.fi, x = ed[v.se];
			while(x) ans[id] -= T.query(dfn[x]), x = fa[x];
		}
	} rep(i, 1, q) printf("%lld\n", ans[i]);
	return 0;
}

