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
using pii = pair < ll, ll >;
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

pii f[N];
int n, K, l, a[N];
ll ans = N + 10;
char s[N];

pii operator + (pii a, pii b) { return pii(a.fi + b.fi, a.se + b.se); }

pii check(int mid) {
	f[0] = { 0, 0 };
	rep(i, 1, n) {
		f[i] = f[i - 1] + pii{ a[i] == 1, 0 };
		chkmin(f[i], f[max(i - l, 0)] + pii{ mid, 1 });
	} return f[n];
}

void solve() {
	int l = 0, r = n;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(mid).se >= K) l = mid + 1;
		else r = mid - 1;
	} auto t = check(l); chkmin(ans, t.fi - 1ll * l * K);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in, l = in;
	scanf("%s", s + 1); rep(i, 1, n) a[i] = s[i] >= 'a' && s[i] <= 'z'; solve();
	rep(i, 1, n) a[i] = a[i] ^ 1; solve(); printf("%lld\n", ans);
	return 0;
}
