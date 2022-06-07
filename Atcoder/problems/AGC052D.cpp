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

int tr[N], n, p[N], f[N], g[N], ans;

void add(int x, int v) { for(; x <= n; x += x & -x) chkmax(tr[x], v); }
int query(int x) { int ret = 0; for(; x; x -= x & -x) chkmax(ret, tr[x]); return ret; }

void solve() {
	n = in; rep(i, 1, n) p[i] = in;
	rep(i, 1, n) tr[i] = 0; ans = 0;
	rep(i, 1, n) add(p[i], f[i] = query(p[i]) + 1), chkmax(ans, f[i]);
	if(ans % 2 == 0) puts("YES");
	else {
		rep(i, 1, n) tr[i] = 0;
		int ret = ans;
		per(i, n, 1) {
			add(n - p[i] + 1, g[i] = query(n - p[i] + 1) + 1);
			if(f[i] == ret) ret--;
			else if(f[i] + g[i] - 1 >= (ans >> 1) + 1) return puts("YES"), void();
		}
		puts("NO");
	} 
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
