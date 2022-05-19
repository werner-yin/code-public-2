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

const int N = 2e5 + 10;

int n, a[N], m, mx[N], pre[N], lpre[N];
map < int, queue < int > > lst;
vec ind[N];

namespace seg {
	int val[N << 2];
	void pu(int o) { val[o] = max(val[o << 1], val[o << 1 | 1]); }
	void build(int o = 1, int l = 1, int r = n) {
		val[o] = 0; if(l == r) return; int mid = l + r >> 1;
		build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	}
	void upd(int p, int v, int o = 1, int l = 1, int r = n) {
		if(l == r) return val[o] = v, void(); int mid = l + r >> 1;
		if(p <= mid) upd(p, v, o << 1, l, mid); else upd(p, v, o << 1 | 1, mid + 1, r); pu(o);
	}
}
	
void solve() {
	n = in, m = in; rep(i, 1, n) a[i] = in, mx[i] = i, pre[i] = 0, ind[i].clear(), lpre[i] = 0;
	rep(i, 1, m) {
		int l = in, r = in;
		chkmin(mx[r], l);
	}
	per(i, n - 1, 1) mx[i] = min(mx[i + 1], mx[i]);
	lst.clear(); map < int, int > lpos;
	rep(i, 1, n) {
		while(lst[a[i]].size() && lst[a[i]].front() < mx[i]) lst[a[i]].pop();
		if(lst[a[i]].size() && lst[a[i]].front() >= mx[i]) {
			pre[i] = lst[a[i]].front(); ind[pre[i]].eb(i);
		} lst[a[i]].push(i);
		if(lpos[a[i]] >= mx[i]) lpre[i] = lpos[a[i]]; lpos[a[i]] = i;
	}
	seg :: build();
	rep(i, 1, n) if(lpre[i]) seg :: upd(i, lpre[i]);
	//rep(i, 1, n) cerr << lpre[i] << " " ; cerr << endl;
	int ans = n;
	rep(i, 1, n) {
		chkmin(ans, max(seg :: val[1], i - 1) - i + 1);
		//	cerr << "!" << i << " " << ans << " " << seg :: val[1] << endl;
		if(pre[i]) break;
		for(auto v : ind[i]) seg :: upd(v, v);
	} printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
