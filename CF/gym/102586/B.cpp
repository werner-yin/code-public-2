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

int n, Q, lpos[N], rpos[N];
ll s[N], a[N], sum[N], S, ans[N];
int lim[N];

ll calc(int x, int r) {
	//cerr << x << " " << r << " : ";
	if(r >= lim[x]) r = lim[x] - 1; //chkmin(r, x + x - 1);
	int l = max(x * 2 - r, 1);
	ll ret = s[r] - s[l - 1], tot = 0;
	ret = max(S - ret, 0ll);
	tot = ret * (r - x + 1) + sum[r] - sum[x] - (s[r] - s[x]) * x + (s[x] - s[l - 1]) * x - (sum[x] - sum[l - 1]);
	//cerr << tot << endl;
	return tot;
}

void calcall(vec &pot, int l, int r) {
	function < void(int, int, int, int)> dfs = [&](int xl, int xr, int l, int r) {
		if(xl > xr) return; int mid = xl + xr >> 1, pos = l; ll tmp = 0, ret = 0;
		rep(i, l, r) if((tmp = calc(i, rpos[pot[mid]])) >= ret) ret = tmp, pos = i;
		chkmax(ans[pot[mid]], ret); dfs(xl, mid - 1, l, pos); dfs(mid + 1, xr, pos, r);
	};
	dfs(0, (int)pot.size() - 1, l, r);
}

namespace seg {
	vec pot[N << 2];
	void ins(int xl, int xr, int v, int o = 1, int l = 1, int r = n) {
		if(xl <= l && r <= xr) return pot[o].eb(v), void(); int mid = l + r >> 1;
		if(xl <= mid) ins(xl, xr, v, o << 1, l, mid); if(xr > mid) ins(xl, xr, v, o << 1 | 1, mid + 1, r);
	}
	void queryall(int o = 1, int l = 1, int r = n) {
		sort(pot[o].begin(), pot[o].end(), [&](int x, int y) { return rpos[x] < rpos[y]; });
		calcall(pot[o], l, r); pot[o].clear(); if(l == r) return; int mid = l + r >> 1;
		queryall(o << 1, l, mid); queryall(o << 1 | 1, mid + 1, r);
	}
}

void solve() {
	rep(i, 1, n) s[i] = s[i - 1] + a[i], sum[i] = sum[i - 1] + i * a[i];
	int pos = 1;
	rep(i, 1, n) {
		while(pos <= n && s[pos] - s[max(2 * i - pos - 1, 0)] < S) pos++;
		lim[i] = pos;
	}
	seg :: queryall();
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, S = lin;
	rep(i, 1, n) a[i] = lin;
	Q = in;
	rep(i, 1, Q) lpos[i] = in, rpos[i] = in;
	rep(i, 1, Q) {
		int mid = lpos[i] + rpos[i] + 1 >> 1;
		seg :: ins(mid, rpos[i], i);
	} solve();
	reverse(a + 1, a + n + 1);
	rep(i, 1, Q) {
		lpos[i] = n - lpos[i] + 1, rpos[i] = n - rpos[i] + 1; swap(lpos[i], rpos[i]);
		int mid = lpos[i] + rpos[i] + 1 >> 1;
		seg :: ins(mid, rpos[i], i);
	} solve(); rep(i, 1, Q) printf("%lld\n", ans[i]);
	return 0;
}
