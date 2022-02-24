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

int n, K, a[N], f[N][2];

void solve() {
	n = in, K = in; rep(i, 1, n) a[i] = in;
	sort(a + 1, a + n + 1);
	map < int, int > cnt;
	rep(i, 1, n) {
		if(a[i] % K == 0 && cnt[a[i] / K]) cnt[a[i] / K]--;
		else cnt[a[i]]++;
	} int ans = 0; for(auto v : cnt) ans += v.se;
	printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif	
	for(int T = in; T; T--) solve();
	return 0;
}
