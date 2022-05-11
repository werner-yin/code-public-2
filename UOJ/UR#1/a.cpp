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
const int V = 1e6;

int n, cnt[N];
ll ans, tret;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) cnt[in]++;
	rep(i, 1, V) ans += 1ll * i * cnt[i], cnt[i] += cnt[i - 1];
	tret = ans;
	rep(i, 2, V) {
		ll tot = tret;
		for(int j = 0; j <= V; j += i) {
			ll r = min(V, j + i - 1);
			tot -= 1ll * (j / i) * (cnt[r] - (j == 0 ? 0 : cnt[j - 1])) * (i - 1);
		} chkmin(ans, tot);
	} cout << ans << endl; return 0;
}
