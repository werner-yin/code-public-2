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
constexpr int mod = 1e9 + 7;

ll f[N], x, y;
int tot;
vector < pair < ll, ll > > ext[1000];

void solve() {
	int ans = 1; x = lin, y = lin; if(x > y) swap(x, y);
	while(ans <= tot - 2 && f[ans + 1] <= x && f[ans + 2] <= y) ans++;
	ll tans = 0;
	for(auto v : ext[ans]) {
		if(v.fi <= x && v.se <= y) {
			tans += (y - v.se) / v.fi + 1;
		}
		if(v.se <= x)
			tans += (x - v.se) / v.fi + 1;
		tans %= mod;
	} if(ans == 1) tans = (tans + x) % mod; printf("%d %lld\n", ans, tans);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	f[0] = f[1] = 1; tot = 1; while(f[tot] < 1e18) f[tot + 1] = f[tot] + f[tot - 1], tot++;
	ext[1].eb(1, 2);
	rep(i, 2, tot) {
		for(auto v : ext[i - 1]) ext[i].eb(v.se, v.fi + v.se);
		ext[i].eb(f[i + 1], f[i - 1] + f[i + 1]);
		//for(auto v : ext[i]) cerr << v.fi << " " << v.se << endl;
		//cerr << endl;
	}
	int Q = in;
	while(Q--) solve();
	return 0;
}
