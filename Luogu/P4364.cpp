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

const int N = 5e5 + 10;

int n, d[N], b[N], tot, ct[N], siz[N], fa[N];
db K;

int s[N << 2], tmn[N << 2], ans[N];

void pu(int o) {
	s[o] = s[o << 1] + s[o << 1 | 1];
	tmn[o] = min(tmn[o << 1 | 1], tmn[o << 1] + s[o << 1 | 1]);
}
void upd(int p, int v, int o = 1, int l = 1, int r = tot) {
	if(l == r) return s[o] += v, tmn[o] = min(s[o], 0), void(); int mid = l + r >> 1;
	if(p <= mid) upd(p, v, o << 1, l, mid); else if(p > mid) upd(p, v, o << 1 | 1, mid + 1, r);
	pu(o);
}
void build(int o = 1, int l = 1, int r = tot) {
	if(l == r) return s[o] = ct[l], tmn[o] = min(s[o], 0), void(); int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); pu(o);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; scanf("%lf", &K); rep(i, 1, n) d[i] = b[i] = in;
	sort(d + 1, d + n + 1); sort(b + 1, b + n + 1); tot = unique(b + 1, b + n + 1) - b - 1;
	rep(i, 1, n) { int p = lower_bound(b + 1, b + tot + 1, d[i]) - b; ct[p]++; }
	build();
	rep(i, 1, n) fa[i] = i / K;
	per(i, n, 1) siz[i]++, siz[fa[i]] += siz[i];
	ans[0] = 1;
	rep(i, 1, n) {
		int l = ans[fa[i]], r = tot;
		if(fa[i]) upd(ans[fa[i]], siz[i]);
		while(l <= r) {
			int mid = l + r >> 1;
			upd(mid, -siz[i]);
			if(tmn[1] >= 0) l = mid + 1; else r = mid - 1;
			upd(mid, siz[i]);
		} ans[i] = l - 1;
		upd(ans[i], -siz[i]);
	} rep(i, 1, n) printf("%d ", b[ans[i]]);
	return 0;
}
