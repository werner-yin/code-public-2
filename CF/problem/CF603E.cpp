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

const int N = 3e5 + 10;

int n, m;
int u[N], v[N], w[N], ans[N], fa[N], siz[N], cur, ind[N];
veg pot;
pii b[N];

int gf(int x) { return fa[x] == x ? x : gf(fa[x]); }
void merge(int x, int y) {
	x = gf(x), y = gf(y); if(x == y) return; cur -= siz[x] & 1; cur -= siz[y] & 1;
	if(siz[x] < siz[y]) swap(x, y); pot.eb(x, y);
	siz[x] += siz[y]; fa[y] = x; cur += siz[x] & 1;
}
void undo() {
	int x, y; tie(x, y) = pot.back(); pot.pop_back(); cur -= siz[x] & 1;
	fa[y] = y; siz[x] -= siz[y]; cur += siz[x] & 1; cur += siz[y] & 1;
}
void solve(int l, int r, int xl, int xr) {
	if(l > r) return; int mid = l + r >> 1, lsz = pot.size();
	rep(i, l, mid) if(ind[i] < xl) merge(u[i], v[i]);
	rep(i, xl, xr) if(b[i].se <= mid) { merge(u[b[i].se], v[b[i].se]); if(!cur) { ans[mid] = i; break; } }
	while(pot.size() > lsz) undo();
	if(!ans[mid]) {
		rep(i, l, mid) if(ind[i] < xl) merge(u[i], v[i]);
		solve(mid + 1, r, xl, xr); while(pot.size() > lsz) undo(); return;
	}
	rep(i, xl, ans[mid] - 1) if(b[i].se < l) merge(u[b[i].se], v[b[i].se]);
	solve(l, mid - 1, ans[mid], xr); while(pot.size() > lsz) undo();
	rep(i, l, mid) if(ind[i] < xl) merge(u[i], v[i]);
	solve(mid + 1, r, xl, ans[mid]); while(pot.size() > lsz) undo();
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	cur = n = in, m = in; rep(i, 1, n) fa[i] = i, siz[i] = 1;
	rep(i, 1, m) u[i] = in, v[i] = in, b[i].fi = w[i] = in, b[i].se = i;
	sort(b + 1, b + m + 1); rep(i, 1, m) ind[b[i].se] = i;
	solve(1, m, 1, m); rep(i, 1, m) ans[i] = ans[i] == 0 ? -1 : b[ans[i]].fi, printf("%d\n", ans[i]);
	return 0;
}
