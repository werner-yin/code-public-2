#include <bits/stdc++.h>

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define in read<int>()
#define lin read<ll>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)
#define epr(i, x, y) for(int i = h[x], y = e[i].v; i; i = e[i].nxt, y = e[i].v)

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

const int N = 5010 + 10;
const int M = 2e5 + 10;

int n, m;
db E;

struct graph {
	struct edge { int v; db w; int nxt; } e[M];
	int cnt, h[N], pre[N]; db dis[N]; bool vis[N];
	void link(int x, int y, db w) { e[++cnt] = (edge) { y, w, h[x] }; h[x] = cnt; }
	void dijk(int S) {
		rep(i, 1, n) dis[i] = 1e18; dis[S] = 0; priority_queue < pair < int, db >, vector < pair < int, db > >, greater <> > q; q.ep(dis[S], S);
		while(q.size()) {
			int x = q.top().se; q.pop(); if(vis[x]) continue; vis[x] = true;
			epr(i, x, y)
				if(dis[y] > dis[x] + e[i].w) 
					dis[y] = dis[x] + e[i].w, pre[y] = i, q.ep(dis[y], y);
		}
	}
} G, R;

struct node { int ed; db val; };
bool operator < (node a, node b) { return a.val < b.val; }

namespace heap {
	const int N = 2e7 + 10;
	node val[N]; int cnt, dis[N], ch[N][2];
	int merge(int x, int y) {
		if(!x || !y) return x | y;
		if(val[y] < val[x]) swap(x, y); int z = ++cnt; val[z] = val[x]; ch[z][0] = ch[x][0]; ch[z][1] = merge(ch[x][1], y);
		if(dis[ch[z][1]] >= dis[ch[z][0]]) swap(ch[z][0], ch[z][1]); dis[z] = dis[ch[z][1]] + 1; return z;
	}
}

int rt[N], id[N], ans;

using heap :: cnt;
using heap :: val;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, scanf("%lf", &E);
	rep(i, 1, m) { int u = in, v = in; db t; scanf("%lf", &t); if(u == n) continue; G.link(u, v, t), R.link(v, u, t); }
	R.dijk(n); rep(i, 1, n) id[i] = i; sort(id + 1, id + n + 1, [&](int x, int y) { return R.dis[x] < R.dis[y]; });
	rep(i, 1, n) {
		int x = id[i];
		for(int i = G.h[x], y = G.e[i].v; i; i = G.e[i].nxt, y = G.e[i].v)
			if(i != R.pre[x]) {
				db delta = G.e[i].w - (R.dis[x] - R.dis[y]);
				//cerr << x << " " << y << " " <<delta << endl;
				++cnt; val[cnt] = (node) { y, delta }; rt[x] = heap :: merge(rt[x], cnt);
			} rt[x] = heap :: merge(rt[x], rt[G.e[R.pre[x]].v]);
		//cerr << "!" << x << " " << rt[x] << " " << G.e[R.pre[x]].v << " " << val[rt[x]].val << endl;
	}
	if(E >= R.dis[1]) ans++, E -= R.dis[1]; else return puts("0"), 0;
	priority_queue < pair < db, int >, vector < pair < db, int > >, greater <> > q; q.ep(R.dis[1] + val[rt[1]].val, rt[1]);
	while(q.size()) {
		auto v = q.top(); q.pop();
		db tv; int x; tie(tv, x) = v;
		if(E >= tv) E -= tv, ans++; else break;
		//cerr << tv << endl;
		if(heap :: ch[x][0]) q.ep(val[heap :: ch[x][0]].val - val[x].val + tv, heap :: ch[x][0]);
		if(heap :: ch[x][1]) q.ep(val[heap :: ch[x][1]].val - val[x].val + tv, heap :: ch[x][1]);
		if(rt[val[x].ed]) q.ep(tv + val[rt[val[x].ed]].val, rt[val[x].ed]);
	} printf("%d\n", ans);
	return 0;
}
