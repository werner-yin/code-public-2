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

const int N = 2.5e5 + 10;

int n, m, t, p[N], pre[62][N];
ll a[N], ans;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, t = in; rep(i, 1, n) a[i] = lin, p[i] = i;
	rep(x, 0, 60) {
		vec pot1, pot2;
		rep(i, 1, n) {
			if(a[p[i]] >> x & 1ll) pot2.eb(p[i]);
			else pot1.eb(p[i]); pre[x][i] = pot1.size();
		}
		rep(i, 1, pot1.size()) p[i] = pot1[i - 1];
		rep(i, pot1.size() + 1, n) p[i] = pot2[i - pot1.size() - 1];
	}
	while(m--) {
		ll v = lin; if(t) v ^= ans >> 20; ans = 0;
		int cur = 0;
		rep(i, 0, 60) {
			if(v >> i & 1ll) {
				ans |= ll((pre[i][n] ^ cur) & 1) << i;
				cur = n - pre[i][n - cur];
			} else {
				ans |= ll((pre[i][n] ^ cur ^ n) & 1) << i;
				cur = cur - pre[i][n] + pre[i][n - cur];
			}
		} printf("%lld\n", ans);
	}
	return 0;
}
