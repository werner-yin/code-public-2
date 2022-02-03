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

int d, c; 
ll a, b;

int getlg(ll x) {
	int cnt = 0;
	while(x) cnt++, x >>= 1; 
	return cnt;
}

ll calc(ll a, ll b) {
	ll ans = 0; int ta = getlg(a), tb = getlg(b);
	while(ta > tb) ans += a, a >>= 1, ta--;
	while(tb > ta) ans += b, b >>= 1, tb--;
	while(a != b) ans += a, a >>= 1, ans += b, b >>= 1;
	ans += a; return ans;
}

#define pw2(x) (1ll << (x))

ll solve1(ll s) {
	ll ans = 0;
	rep(i, 2, d) {
		ll x = s / (pw2(i) - 1), ret = s - (pw2(i) - 1) * x;
		if(x <= 0) break; if(getlg(x) + i - 1 > d) continue;
		per(j, i - 1, 0) if(ret >= pw2(j) - 1) ret -= pw2(j) - 1;
		if(ret == 0) ans++;
	} return ans;
}

ll f[60][220][2], s;

ll solve2(ll s) {
	ll ans = 0;
	rep(li, 2, d) {
		rep(lj, 2, d) {
			ll x = (s + 1 - pw2(lj - 1)) / (pw2(li) + pw2(lj) - 3);
			if(x <= 0) break; if(getlg(x) + max(li, lj) - 1 > d) continue;
			ll ret = (s + 1 - pw2(lj - 1)) - x * (pw2(li) + pw2(lj) - 3);
			rep(len, 0, li + lj - 4) if(~(ret + len) & 1ll){
				ret += len; int t = getlg(ret) + 1;
				rep(i, 1, t) rep(j, 0, min((i - 1) << 1, len)) f[i][j][0] = f[i][j][1] = 0;
				f[1][0][0] = 1;
				rep(i, 1, t - 1) rep(j, 0, min((i - 1) << 1, len)) rep(v, 0, 1) if(f[i][j][v]) {
					int ea = i < li - 1, eb = i < lj - 1;
					rep(a, 0, ea) rep(b, 0, eb) if(((a + b + v) & 1) == (ret >> i & 1ll)) f[i + 1][j + a + b][(a + b + v) >> 1] += f[i][j][v];
				} ans += f[t][len][0];
				ret -= len;
			}
		}
	} return ans;
}

void solve() {
	d = 60, s = lin;
	printf("%lld\n", solve1(s) + solve2(s) + 1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	int T = 1;	while(T--) solve();
	return 0;
}
