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

int n, a[N], cnt[N], res[N], lst[N];

void solve() {
	n = in; rep(i, 1, n) a[i] = in;
	sort(a + 1, a + n + 1); res[0] = 1; res[1] = 0;
	for(int t = 2; t / 2 <= n; t <<= 1) 
		rep(i, (t >> 1) + 1, min(n, t)) res[i] = t - i;
	lst[0] = 0; lst[n] = n;
	rep(i, 1, n - 1)
		lst[i] = a[i] == a[i + 1] ? lst[i - 1] : i;
	int ans = res[n] + 1 + 1;
	for(int t = 1; t <= n; t <<= 1) {
		rep(i, 0, n) if(lst[i] == i) {
			int len1 = i, len2 = lst[min(n, len1 + t)] - len1, len3 = n - len1 - len2;
			chkmin(ans, res[len1] + res[len2] + res[len3]);
		}
	}
	printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
