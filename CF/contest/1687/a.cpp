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

int n, K;
int a[N];
ll s[N], ts[N];

void solve() {
	n = in, K = in; rep(i, 1, n) a[i] = in, s[i] = s[i - 1] + a[i];
	ll ans = 0;
	if(K <= n) {
		rep(i, K, n) chkmax(ans, s[i] - s[i - K]);
		rep(i, 1, K - 1) ans += i;
	} else if(n != 1) {
		ans = s[n]; K -= n;
		rep(i, 1, n - 1) ts[i] = ts[i - 1] + i * 2;
		ll reta = 0;
		rep(i, 1, n) if(K - i + 1 >= 0) {
			ll ret = 0;
			ret = (ts[n - 1]) * ((K - i + 1) / (n - 1)) + ts[(K - i + 1) % (n - 1)] + ts[n - 1] + 1ll * (i - 2) * (i - 1) / 2;
			chkmax(reta, ret);
		} ans += reta;
	} else {
		ans = s[n] + K - 1;
	} cout << ans << endl;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
