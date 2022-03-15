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

const int N = 1.5e6 + 10;

veg G[N];
int n, K, a[N], b[N], c[N], fa[N], st, ed, res[2], tres[2];
bool vis[N], vise[N], marked[N];
vec pot, pote;

void mrk(int x, int p) {
	while(x != p) marked[x] = true, x = fa[x];
	marked[x] = true;
}

void dfs(int x, int p) {
	fa[x] = p; vis[x] = true; pot.eb(x);
	for(auto v : G[x]) {
		int y, id; tie(y, id) = v;
		if(vise[id]) continue; vise[id] = true; pote.eb(id);
		if(vis[y]) st = x, ed = y, mrk(x, y);
		else dfs(y, x);
	}
}

void tdfs(int x, int w) {
	if(!marked[x]) res[x > n] += w; else tres[x > n] += w; vis[x] = true; 
	for(auto v : G[x]) {
		int y, id; tie(y, id) = v;
		if(vise[id]) continue; vise[id] = true;
		if(vis[y]) { tres[y > n] += c[id]; continue; }
		tdfs(y, c[id]);
	}
}

int ans[2];
veg fle;

namespace sub1 {
	const int N = 1e6 + 10;
	void solve() {
		bitset < N << 1 > f;
		auto bag = [&](int siz, int val) {
					   for(int i = 1; i <= siz; i <<= 1) 
						   f = (f << (val * i)) | (f >> (val * i)), siz -= i;
					   if(siz) f = (f << (val * siz)) | (f >> (val * siz));
				   };
		f[ans[0] - ans[1] + N] = true;
		vec pot; for(auto v : fle) pot.eb(v.se - v.fi);
		sort(pot.begin(), pot.end());
		rep(i, 0, int(pot.size()) - 1) {
			int j = i; while(j < pot.size() && pot[i] == pot[j]) j++;
			bag(j - i, pot[i]); i = j - 1;
		}
		rep(i, 0, K) if(f[i + N] || f[N - i]) return puts("YES"), void();
		puts("NO");
	}
}

int main() {
	n = in, K = in;
	rep(i, 1, n << 1) a[i] = in, b[i] = in, c[i] = in, G[a[i]].eb(b[i] + n, i), G[b[i] + n].eb(a[i], i);
	rep(i, 1, n << 1) if(G[i].size() == 0) return puts("NO"), 0;
	rep(i, 1, n << 1) if(!vis[i]) {
		res[0] = res[1] = tres[0] = tres[1] = 0; st = ed = 0; dfs(i, 0);
		assert(st && ed); for(auto v : pot) vis[v] = false; for(auto v : pote) vise[v] = false;
		pot.clear(); pote.clear(); tdfs(st, 0);
		ans[0] += res[0]; ans[1] += res[1]; fle.eb(tres[0], tres[1]);
	}
	for(auto &v : fle) if(v.fi > v.se) swap(v.fi, v.se);
	sub1 :: solve(); return 0;
}
