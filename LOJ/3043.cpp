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
const int mod = 998244353;
const int inv2 = (mod + 1) >> 1;

struct node {
	int a, b, c, d;
} val[N << 2];

ll pw, sum;
int n, m;

node operator + (node a, node b) {
	node c;
	sum = ((sum - a.c - a.d) % mod + mod) % mod;
	c.a = (a.a + b.a) % mod, c.b = (a.b + b.b) % mod, c.c = (a.c + b.c) % mod, c.d = (a.d + b.d) % mod;
	c.a = 1ll * c.a * inv2 % mod; c.b = 1ll * c.b * inv2 % mod;
	c.c = 1ll * c.c * inv2 % mod; c.d = 1ll * c.d * inv2 % mod;
	sum = (sum + c.c + c.d) % mod;
	return c;
}

int stu(int xl, int xr, int l, int r) { if(xl <= l && r <= xr) return 1; else if(l > xr || r < xl) return 0; else return 2; }

void build(int o = 1, int l = 1, int r = n) {
	val[o].a = 1; if(l == r) return; int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
}

void upd(int xl, int xr, int lst, int o = 1, int l = 1, int r = n) {
	int cur = stu(xl, xr, l, r);
	if(lst == 1) { // tp 2: lst = 1, cur = 1
		assert(cur == 1); node tval; tval.b = (val[o].b + val[o].a) % mod; tval.a = 0; tval.d = (val[o].d + val[o].c) % mod; tval.c = 0;
		val[o] = val[o] + tval; //return;
	} else { //assert(lst == 2);
		if(cur == 0) { // tp3 : lst = 2, cur = 0
			node tval; tval.c = (val[o].b + val[o].d) % mod; tval.b = 0; tval.d = 0; tval.a = (val[o].a + val[o].c) % mod; 
			val[o] = val[o] + tval; return;
		}
		if(cur == 1) { // tp4 : lst = 2, cur = 1
			node tval; tval.a = tval.b = tval.d = 0; tval.c = 1; val[o] = val[o] + tval;
		}
		if(cur == 2) { // tp5 : lst = 2, cur = 2
			node tval; tval.a = 1; tval.b = tval.c = tval.d = 0; val[o] = val[o] + tval;
		}
	}
	if(l == r) return; int mid = l + r >> 1;
	upd(xl, xr, cur, o << 1, l, mid); upd(xl, xr, cur, o << 1 | 1, mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; build(); pw = 1;
	while(m--) {
		int op = in, l, r;
		if(op == 1) l = in, r = in, upd(l, r, 2), pw = pw * 2ll % mod;
		else printf("%lld\n", pw * sum % mod);
	}
	return 0;
}
