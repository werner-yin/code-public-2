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

int n, m, tim;
char s[114];

namespace seg {
	const int N = 6e6 + 10;
	int ch[N][2], ndn, tms[N]; pii val[N];
	int nd(pii v) { int x = ++ndn; val[x] = v; return x; }
	int copy(int x) { if(tms[x] == tim) return x; int y = ++ndn; val[y] = val[x], ch[y][0] = ch[x][0], ch[y][1] = ch[x][1]; tms[y] = tms[x]; return y; }
	void upd(int p, pii v, int &x, int l = 1, int r = n) {
		x = copy(x); if(l == r) return val[x] = v, void(); int mid = l + r >> 1;
		if(p <= mid) upd(p, v, ch[x][0], l, mid); else upd(p, v, ch[x][1], mid + 1, r);
	}
	pii query(int p, int x, int l = 1, int r = n) {
		if(l == r) return val[x]; int mid = l + r >> 1;
		if(p <= mid) return query(p, ch[x][0], l, mid); else return query(p, ch[x][1], mid + 1, r); 
	}
	void build(int &x, int l = 1, int r = n) {
		x = nd({ 0, 0 }); if(l == r) return val[x].fi = l, void(); int mid = l + r >> 1;
		build(ch[x][0], l, mid); build(ch[x][1], mid + 1, r);
	}
}

struct node {
	int rt, toted, mxcnt; ll totw; 
} stk[N];
int tot;

int gf(int id, int x) { int t; while((t = seg :: query(x, id).fi) != x) x = t; return x; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; node lst = (node) { 0, 0, 0, 0 };
	seg :: build(lst.rt);
	rep(i, 1, m) {
		scanf("%s", s + 1); tim = i;
		if(s[1] != 'R') {
			tot = lst.mxcnt, stk[tot] = lst;
		}
		if(s[1] == 'A') {
			lst = stk[tot]; lst.mxcnt++;
			int x = in, y = in, fx = gf(lst.rt, x), fy = gf(lst.rt, y);
			if(fx != fy) {
				int dx = seg :: query(fx, lst.rt).se, dy = seg :: query(fy, lst.rt).se;
				if(dx > dy) swap(dx, dy), swap(x, y), swap(fx, fy);
				seg :: upd(fx, pii(fy, 114), lst.rt); if(dx == dy) seg :: upd(fy, pii(fy, dy + 1), lst.rt); lst.toted++; lst.totw += i;
			}
		} else if(s[1] == 'D') {
			lst = stk[tot - in];
		} else {
			lst = stk[tot];
		} printf("%lld\n", lst.toted == n - 1 ? lst.totw : 0);
	}
	return 0;
}
