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

template < typename T > void chkmax(T &x, const T &y) { x = x < y ? y : x; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 1e6 + 10;

int n;
ll sb[N], sa[N], sc[N], tota;
pii val[N];

struct frac {
	ll x, y;
	void reduce() { ll t = __gcd(x, y); x /= t, y /= t; }
	frac(ll x = 0, ll y = 1) : x(x), y(y) { reduce(); }
	friend frac operator + (frac a, ll b) { return frac(a.x + b * a.y, a.y); }
	friend bool operator < (frac a, frac b) { return (__int128)a.x * b.y < (__int128)a.y * b.x; }
} ans;

ll calc(int x, int y) {
	ll t = max(val[x].fi, val[x].se), ret = sc[y];
	if(max(val[y].fi, val[y].se) <= t) ret -= t; return ret;
}

int get(int x) {
	int l = 1, r = n, ans = -1;
	while(l <= r) {
		int mid = l + r >> 1;
		if(calc(x, mid) >= tota - val[x].se) ans = mid, r = mid - 1;
		else l = mid + 1;
	} return ans;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; ans = frac(n, 1); rep(i, 1, n) val[i].fi = in, val[i].se = in;
	sort(val + 1, val + n + 1, [&](auto x, auto y) { return max(x.fi, x.se) > max(y.fi, y.se); });
	rep(i, 1, n) sa[i] = sa[i - 1] + val[i].fi, sb[i] = sb[i - 1] + val[i].se, sc[i] = sc[i - 1] + max(val[i].fi, val[i].se);
	tota = sa[n];
	rep(i, 1, n) {
		int pos = get(i); if(pos < 0) continue; ll ret = calc(i, pos); if(ret > tota) continue;
		if(max(val[pos].fi, val[pos].se) <= max(val[i].fi, val[i].se)) pos--;
		frac tans(tota - ret, val[i].se); tans = tans + pos; chkmin(ans, tans);
#ifdef YJR_2333_TEST
		cerr << pos << " " << ret << " " << tota << " " << tans.x << " " << tans.y << endl;
#endif
	} ans.y *= n; ans.x = ans.y - ans.x; ans.reduce();
	cout << ans.x << " " << ans.y << endl;
	return 0;
}
