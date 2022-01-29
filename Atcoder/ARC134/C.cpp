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
const int mod = 998244353;

int inv[N], n, K;
ll a[N];

ll C(int x, int t) {
	ll res = 1;
	rep(i, 1, t) {
		res = 1ll * res * inv[i] % mod * (x - i + 1) % mod;
	} return res;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; rep(i, 1, n) a[i] = in;
	rep(i, 2, n) a[1] -= a[i];
	a[1] -= K; if(a[1] < 0) return puts("0"), 0;
	inv[1] = 1; rep(i, 2, K) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
	int ans = 1;
	rep(i, 1, n) ans = 1ll * ans * C(a[i] + K - 1, K - 1) % mod;
	cout << ans << endl;
	return 0;
}
