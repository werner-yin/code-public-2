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

int n, a[N], b[N], pre[N], suf[N];
pii pot[N];
ll ret, ans;
bool vis[N][2];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in, b[i] = in, pot[i] = { a[i], i }, pot[i + n] = { b[i], i };
	sort(pot + 1, pot + 2 * n + 1);
	rep(i, 1, n) {
		int x = pot[i].se, y = 0; if(x > n) x -= n, y = 1; ans += pot[i].fi;
		vis[x][y] = true;
	} ret = ans;
	rep(i, 1, n) if(!vis[i][0] && !vis[i][1]) return cout << ans << endl, 0;
	ans = 1e18; pre[0] = suf[n + 1] = 0;
	rep(i, 1, n) pre[i] = max(pre[i - 1], min(a[i], b[i]));
	per(i, n, 1) suf[i] = max(suf[i + 1], min(a[i], b[i]));
	rep(i, 1, n) {
		chkmin(ans, max(a[i], b[i]) - max(pre[i - 1], suf[i + 1]) + ret);
	}
	ll tota = 0, totb = 0;
	rep(i, 1, n) tota += a[i], totb += b[i];
	chkmin(ans, tota); chkmin(ans, totb);
	cout << ans << endl;
	return 0;
}
