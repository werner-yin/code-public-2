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

char s[N];
int bel[N], id[N], n, ndn, q, rt, mat[N], deg[N], pl[N], dep[N], fa[N];

int build(int l, int r, int d) {
	int x = ++ndn; bel[l] = x; bel[r] = x; pl[x] = l; dep[x] = d; l++; r--;
	rep(i, l, r) {
		if(mat[i]) {
			int y = build(i, mat[i], d + 1);
			fa[y] = x; i = mat[i]; ++deg[x];
		}
	}
	return x;
}

struct node {
	ll val; int mn, cnt;
	node(ll _v = 0, int _mn = 1e9, int _cnt = 0) : val(_v), mn(_mn), cnt(_cnt) {}
};

namespace seg {
	node val[N << 2];
	node operator + (node a, node b) {
		node c; if(a.mn > b.mn) swap(a, b);
		c = a; c.val += b.val; if(b.mn == c.mn) c.cnt += b.cnt; return c;
	}
	void upd(int pos, node v, int o = 1, int l = 1, int r = n) {
		if(l == r) return val[o] = v, void(); int mid = l + r >> 1;
		if(pos <= mid) upd(pos, v, o << 1, l, mid); else upd(pos, v, o << 1 | 1, mid + 1, r);
		val[o] = val[o << 1] + val[o << 1 | 1];
	}
	node query(int xl, int xr, int o = 1, int l = 1, int r = n) {
		if(xl == l && xr == r) return val[o]; int mid = l + r >> 1;
		if(xr <= mid) return query(xl, xr, o << 1, l, mid); else if(xl > mid) return query(xl, xr, o << 1 | 1, mid + 1, r);
		else return query(xl, mid, o << 1, l, mid) + query(mid + 1, xr, o << 1 | 1, mid + 1, r);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; q = in;
	scanf("%s", s + 1);
	static int stk[N]; int top = 0;
	rep(i, 1, n) {
		if(s[i] == '(') stk[++top] = i;
		else if(top) {
			int v = stk[top]; top--;
			mat[v] = i; mat[i] = v;
		}
	} 
	rep(i, 1, n) if(mat[i]) build(i, mat[i], 1), i = mat[i];
	rep(i, 1, n) if(mat[i] > i) seg :: upd(i, node(1ll * deg[bel[i]] * (deg[bel[i]] - 1) / 2 + 1, dep[bel[i]], 1));
	while(q--) {
		int t = in, l = in, r = in;
		if(t == 1) {
			seg :: upd(l, node());
			if(fa[bel[l]])
				deg[fa[bel[l]]]--, seg :: upd(pl[fa[bel[l]]], node(deg[fa[bel[l]]] * (deg[fa[bel[l]]] - 1) / 2 + 1, dep[bel[l]] - 1, 1 ));
		} else {
			node v = seg :: query(l, r);
			ll ans = v.val + 1ll * v.cnt * (v.cnt - 1) / 2;
			printf("%lld\n", ans);
		}
	}
	return 0;
}
