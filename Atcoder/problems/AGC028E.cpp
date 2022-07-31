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
const int inf = 0x3f3f3f3f;

int n, a[N], val[N], cnt[N];

struct seg {
	int val[N << 2];
	void build(int o = 1, int l = 1, int r = n) {
		val[o] = -inf; if(l == r) return; int mid = l + r >> 1;
		build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); 
	}
	void upd(int pos, int v, int o = 1, int l = 1, int r = n) {
		if(l == r) return val[o] = v, void(); int mid = l + r >> 1;
		pos <= mid ? upd(pos, v, o << 1, l, mid) : upd(pos, v, o << 1 | 1, mid + 1, r); val[o] = max(val[o << 1], val[o << 1 | 1]);
	}
	int query(int xl, int xr, int o = 1, int l = 1, int r = n) {
		if(xl <= l && r <= xr) return val[o]; int mid = l + r >> 1, ans = -inf;
		if(xl <= mid) chkmax(ans, query(xl, xr, o << 1, l, mid)); if(xr > mid) chkmax(ans, query(xl, xr, o << 1 | 1, mid + 1, r));
		return ans;
	}
} O, E;

char ans[N];
int pmx, pmy, mx, my;

bool check(int lim, int v) {
	if(v < 0) return 0;
	if(v & 1) return O.query(lim, n) >= v;
	else return E.query(lim, n) >= v;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in;
	int mxv = 0;
	rep(i, 1, n) 
		val[i] = a[i] > mxv ? 2 : 1, chkmax(mxv, a[i]);
	O.build();
	per(i, n, 1) {
		int vo = O.query(a[i], n), ve = E.query(a[i], n);
		if(val[i] & 1) O.upd(a[i], val[i] + ve), E.upd(a[i], val[i] + vo);
		else O.upd(a[i], val[i] + vo), E.upd(a[i], val[i] + ve);
	}
	per(i, n, 1) cnt[i] = cnt[i + 1] + val[i] - 1;
	rep(i, 1, n) {
		O.upd(a[i], -inf), E.upd(a[i], 0);
		if(check(my, pmx + (a[i] > mx) + cnt[i + 1] - pmy) || check(max(a[i], mx), pmy + cnt[i + 1] - pmx - (a[i] > mx)))
			ans[i] = '0', pmx += a[i] > mx, chkmax(mx, a[i]);
		else ans[i] = '1', pmy += a[i] > my, chkmax(my, a[i]);
	}
	if(pmx != pmy) return puts("-1"), 0;
	puts(ans + 1);
	return 0;
}
