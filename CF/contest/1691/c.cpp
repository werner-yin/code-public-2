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

int n, K, lpos[N], rpos[N];
char s[N];
ll tot = 0;

void solve() {
	n = in, K = in; tot = 0; scanf("%s", s + 1);
	rep(i, 0, 9) lpos[i] = rpos[i] = 0;
	rep(i, 1, n) {
		int x = s[i] - '0'; tot += x;
		lpos[x] = lpos[x] ? lpos[x] : i;
		rpos[x] = i;
	}
	tot *= 11; ll ans = tot;
	rep(x, 0, 9)
		rep(y, 0, 9) if(lpos[x] && rpos[y]) {
		int a = lpos[x], b = rpos[y];
		if(a == b) continue;
		int oper = a - 1 + n - b - (a > b);
		if(oper <= K) chkmin(ans, tot - x - y * 10);
	} // two
	rep(x, 0, 9) if(lpos[x]) {
		int oper = lpos[x] - 1;
		if(oper <= K) chkmin(ans, tot - x);
	}
	rep(x, 0, 9) if(rpos[x]) {
		int oper = n - rpos[x];
		if(oper <= K) chkmin(ans, tot - x * 10);
	}
	printf("%lld\n", ans);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
