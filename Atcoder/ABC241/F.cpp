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

int h, w, n;
int sx, sy, gx, gy;
int x[N], y[N], dis[N], tot;
vec G[N];

map < int, set < int > > f, g;
map < pii, int > id;

int tx[N], ty[N];

bool ip(int x, int y) { return x > 0 && y > 0 && x <= h && y <= w; }
int gid(int x, int y) {
	if(id[{ x, y }]) return id[{ x, y }];
	++tot, tx[tot] = x, ty[tot] = y, id[{ x, y }] = tot;
	return tot;
}

int S = 1, T = 2;

const pii H[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	h = in, w = in, n = in;
	sx = in, sy = in; gx = in, gy = in;
	rep(i, 1, n) {
		x[i] = in, y[i] = in;
		f[x[i]].insert(y[i]);
		g[y[i]].insert(x[i]);
	}
	S = gid(sx, sy); T = gid(gx, gy);
	rep(i, 1, n) {
		rep(k, 0, 3) {
			int tx = x[i] + H[k].fi, ty = y[i] + H[k].se;
			if(ip(tx, ty)) gid(tx, ty);
		}
	} 
	int ltot = tot;
	rep(i, 1, ltot) {
		int x = tx[i], y = ty[i];
		//		cerr << x << " " << y << endl;
		
		auto it = f[x].lower_bound(y + 1);
		if(it != f[x].end()) /*cerr << "R: " << x << " " << *it - 1 << endl, */G[i].eb(gid(x, *it - 1));
		it = f[x].lower_bound(y);
		if(it != f[x].begin()) it--, /*cerr << "R: " << x << " " << *it + 1 << endl, */G[i].eb(gid(x, *it + 1));
		
		it = g[y].lower_bound(x + 1);
		if(it != g[y].end()) G[i].eb(gid(*it - 1, y));
		it = g[y].lower_bound(x);
		if(it != g[y].begin()) it--, G[i].eb(gid(*it + 1, y));
	}// rep(i, ltot + 1, tot) cerr << "!" << tx[i] << " " << ty[i] << endl;
	queue < int > q; q.ep(S); dis[S] = 1;
	while(q.size()) {
		int x = q.front(); q.pop(); //cerr << "!" << x << " " << tx[x] << " " << ty[x] << endl;
		for(auto v : G[x]) if(!dis[v]) dis[v] = dis[x] + 1, q.ep(v);
	} printf("%d\n", dis[T] - 1);
	return 0;
}
