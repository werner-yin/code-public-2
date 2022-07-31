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

int n, x;
int ans[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, x = in;
	if(x == 1 || x == 2 * n - 1) return puts("No"), 0;
	int v = x >= n ? n + n - 1 : 1;
	ans[n] = v, ans[n + 1] = x;
	vec pot; rep(i, 1, n + n - 1) if(i != v && i != x) pot.eb(i);
	reverse(pot.begin(), pot.end());
	rep(i, 1, n + n - 1) {
		if(!ans[i]) ans[i] = pot.back(), pot.pop_back();
	} puts("Yes");
	rep(i, 1, n + n - 1) printf("%d\n", ans[i]);
	return 0;
}
