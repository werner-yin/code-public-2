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

int n, m, a[N], b[N], K;

veg red(veg p) {
	veg ret;
	for(auto v : p)
		if(ret.size() && v.fi == ret.back().fi) ret.back().se += v.se;
		else ret.eb(v);
	return ret;
}

void solve() {
	n = in, m = in;
	rep(i, 1, n) a[i] = in;
	K = in;
	rep(i, 1, K) b[i] = in;
	veg pot1, pot2;
	rep(i, 1, n) {
		int t = a[i]; while(t % m == 0) t /= m;
		pot1.eb(t, a[i] / t);
	}
	rep(i, 1, K) {
		int t = b[i]; while(t % m == 0) t /= m;
		pot2.eb(t, b[i] / t);
	}
	pot1 = red(pot1), pot2 = red(pot2);
	puts(pot1 == pot2 ? "Yes" : "No");
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
