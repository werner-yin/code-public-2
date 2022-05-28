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
ll sb[N], sa[N];
pii val[N];

struct frac {
	ll x, y;
	void reduce() { ll t = __gcd(x, y); x /= t, y /= t; }
	frac(ll x = 0, ll y = 1) : x(x), y(y) { reduce(); }
	friend frac operator + (frac a, ll b) { return frac(a.x + b * a.y, a.y); }
	friend bool operator < (frac a, frac b) { return a.x * b.y < a.y * b.x; }
} ans;

ll tr[N];
void add(int x, ll v) { for(; x <= n; x += x & -x) tr[x] += v; }
ll query(int x) { ll ret = 0; for(; x; x -= x & -x) ret += tr[x]; return ret; }
int ttr[N];
void alef(int x, int v) { for(; x <= n; x += x & -x) ttr[x] += v; }
int qlef(int x) { int ret = 0; for(; x; x -= x & -x) ret += ttr[x]; return ret; }

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) val[i].fi = in, val[i].se = in;
	sort(val + 1, val + n + 1, [&](auto x, auto y) { return max(x.fi, x.se) < max(y.fi, y.se);return x.se ^ y.se ? x.se < y.se : x.fi < y.fi; });
	rep(i, 1, n) sa[i] = sa[i - 1] + val[i].fi, sb[i] = sb[i - 1] + val[i].se, add(i, val[i].se), alef(i, 1);
	ll tota = sa[n], totb = sb[n]; int cur = 0;
	//rep(i, 1, n) cerr << val[i].fi << " " ; cerr << endl;
	//rep(i, 1, n) cerr << val[i].se << " " ; cerr << endl;
	per(i, n, 0) {
		//while(cur > i) cur--;
		while(cur < n && totb - query(cur + 1) >= tota) cur++;
		//cerr << i << " " << cur << " " << tota << " " << totb << endl;
		//if(cur > i) break;
		//assert(totb - query(cur) - tota >= 0);
		frac tans;
		if(cur + 1 <= n) tans = frac(max((totb - query(cur)) - tota, (ll)0), val[cur + 1].se);
		//cerr << tans.x << " " << tans.y << endl;
		tans = tans + qlef(cur); tans.y = tans.y * n; tans.reduce(); chkmax(ans, tans); 
		if(i && val[i].fi > val[i].se) {
			tota -= val[i].fi, totb -= val[i].se, add(i, -val[i].se); val[i].se = 0; alef(i, -1);
		}
	}
	function< void(ll) > twrite = [&](ll x) { if(x >= 10) twrite(x / 10); putchar(x % 10 + '0'); };
	auto write = [&](ll t) { if(t == 0) putchar('0'); else assert(t >= 0), twrite(t); };
	write(ans.x), putchar(' '), write(ans.y);
	return 0;
}
