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
const int M = 1e7 + 10;

int ndn, n, a[N], id[N], ind[N], tot, tim, dfn[N], R[N];
int val[N << 2];
vec G[N], T[N];
bool tvis[N];
vec F[M];
int dis[M];

int fa[N];

void pu(int x) {
	if(!val[x << 1] || !val[x << 1 | 1]) val[x] = val[x << 1] | val[x << 1 | 1];
	else ++tot, val[x] = tot, F[tot].eb(val[x << 1]), F[tot].eb(val[x << 1 | 1]), F[val[x << 1]].eb(tot), F[val[x << 1 | 1]].eb(tot);
}

void upd(int x, int o = 1, int l = 1, int r = n) {
	if(l == r) return val[o] = val[o] ? 0 : ind[l], void(); int mid = l + r >> 1;
	if(x <= mid) upd(x, o << 1, l, mid); else upd(x, o << 1 | 1, mid + 1, r); pu(o);
}

void linkit(int xl, int xr, int fr, int o = 1, int l = 1, int r = n) {
	if(xl <= l && r <= xr) return (val[o] && (F[fr].eb(val[o]), F[val[o]].eb(fr), 1)), void(); int mid = l + r >> 1;
	if(xl <= mid) linkit(xl, xr, fr, o << 1, l, mid); if(xr > mid) linkit(xl, xr, fr, o << 1 | 1, mid + 1, r);
}

int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }

void dfs(int x, int p) {
	//cerr << x << endl;
	dfn[x] = ++tim; ind[tim] = x;
	for(auto y : T[x]) assert(y != p), dfs(y, x);
	R[x] = tim;
}

void rdfs(int x, int p) {
	linkit(dfn[x], R[x], x); upd(dfn[x]);
	for(auto y : G[x]) rdfs(y, x);
	upd(dfn[x]);
}

void solve() {
	n = in; rep(i, 1, n) a[i] = in;
	rep(i, 0, n + 1) fa[i] = i, id[i] = i;
	rep(i, 0, n + 1) tvis[i] = false;
	sort(id + 1, id + n + 1, [&](int x, int y) { return a[x] < a[y]; });
	rep(i, 1, n) {
		int x = id[i]; tvis[x] = true;
		int l = gf(x - 1), r = gf(x + 1);
		//cerr << x << " " << l << " " << tvis[l] << " " << r << " " <<  tvis[r] << endl;
		if(tvis[l]) G[x].eb(l), fa[l] = x;
		if(tvis[r]) G[x].eb(r), fa[r] = x;
	} int rta = gf(1);
	//rep(x, 1, n) for(auto y : G[x]) cerr << x << "->"<<y << endl;
	reverse(id + 1, id + n + 1);
	rep(i, 0, n + 1) tvis[i] = false, fa[i] = i;
	rep(i, 1, n) {
		int x = id[i]; tvis[x] = true;
		int l = gf(x - 1), r = gf(x + 1);
		if(tvis[l]) T[x].eb(l), fa[l] = x;
		if(tvis[r]) T[x].eb(r), fa[r] = x;
	} int rtb = gf(1);
	//rep(x, 1, n) for(auto y : T[x]) cerr << x << "->"<<y << endl;
	//cerr << "---" << endl;
	tim = 0; dfs(rtb, 0);
	//rep(x, 1, n) cerr << dfn[x] << " " << R[x] << endl;
	tot = n; rdfs(rta, 0);
	queue < int > q; rep(i, 1, tot) dis[i] = 0; q.ep(1); dis[1] = 1;
	//cerr << "!" << tot << endl;
	while(q.size()) {
		int x = q.front(); q.pop();
		if(x == n) return printf("%d\n", dis[n] - 1), void();
		for(auto y : F[x]) if(!dis[y]) dis[y] = dis[x] + 1, q.ep(y);
	} cerr << "!" << endl; exit(0);
}

void clr() {
	rep(i, 1, tot) dis[i] = 0, F[i].clear();
	rep(i, 1, n) a[i] = id[i] = ind[i] = dfn[i] = R[i] = 0, G[i].clear(), T[i].clear(), tvis[i] = 0;
	rep(i, 1, n << 2) val[i] = 0;
	tot = 0, tim = 0;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(), clr(); return 0;
}
