#include <bits/stdc++.h>

#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

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
const int T = 30;

int n, p[N], a[N], rt[N];

namespace seg {
	const int N = 1e7 + 10;
	int ch[N][2], val[N], ndn;
	int nd(int v) { int x = ++ndn; val[x] = v; ch[x][0] = ch[x][1] = 0; return x; }
	int cp(int o) { int x = ++ndn; val[x] = val[o]; ch[x][0] = ch[o][0], ch[x][1] = ch[o][1]; return x; }
	void pu(int o) { val[o] = min(val[ch[o][0]], val[ch[o][1]]); }
	void init() { val[0] = inf; }
	void upd(int &x, int p, int v, int l = 0, int r = n + T) {
		x = cp(x); if(l == r) return chkmin(val[x], v), void(); int mid = l + r >> 1;
		if(p <= mid) upd(ch[x][0], p, v, l, mid); else upd(ch[x][1], p, v, mid + 1, r); pu(x);
	}
	int query(int x, int xl, int xr, int l = 0, int r = n + T) {
		if(!x) return inf; if(xl <= l && r <= xr) return val[x]; int mid = l + r >> 1, ans = inf;
		if(xl <= mid) chkmin(ans, query(ch[x][0], xl, xr, l, mid));
		if(xr > mid) chkmin(ans, query(ch[x][1], xl, xr, mid + 1, r)); return ans;
	}
	void build(int &o, int l = 0, int r = n + T) {
		o = nd(inf); if(l == r) return; int mid = l + r >> 1;
		build(ch[o][0], l, mid), build(ch[o][1], mid + 1, r); 
	}
};

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) p[i] = in; rep(i, 1, n) a[i] = in;
	seg :: init(); seg :: build(rt[0]); seg :: upd(rt[0], 0, 0); seg :: upd(rt[0], 1, a[1]);
	rep(i, 1, n) {
		rt[i] = rt[i - 1];
		seg :: upd(rt[i], i + p[i], seg :: query(rt[i - 1], i, n + T));
		int mxp = i - 1;
		per(j, i - 1, 1) {
			//if(i - p[i] > j) break;
			seg :: upd(rt[i], mxp, seg :: query(rt[j], max(i - p[i] - 1, 0), n + T));
			chkmax(mxp, j + p[j]);
		}
		seg :: upd(rt[i], i, seg :: query(rt[i], i - 1, n + T) + a[i]);
		if(i < n) seg :: upd(rt[i], i + 1, seg :: query(rt[i], i, n + T) + a[i + 1]);
	}
	cout << seg :: query(rt[n], n, n + T) << endl;
	return 0;
}
