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
using pii = pair < int, ll >;
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

int n, m;
ll ans, dis[N], A[N];
veg T[N];
vec G[N];
bool ok1[N], ok2[N];

void dfs(int x, ll tdis) {
	if(dis[x] != -1) return ans = __gcd(ans, dis[x] - tdis), void();
	dis[x] = tdis;
	for(auto y : T[x]) dfs(y.fi, tdis + y.se);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 1, m) {
		int u = in, v = in;
		G[u].eb(v);
	}
	ok1[1] = ok2[n] = 1;
	rep(i, 1, n) if(ok1[i]) for(auto y : G[i]) ok1[y] = true;
	per(i, n, 1) for(auto y : G[i]) ok2[i] |= ok2[y];
	rep(i, 1, n) A[i] = lin;
	rep(i, 1, n) if(ok1[i] && ok2[i]) {
		if(A[i] != -1) {
			T[i << 1].eb(i << 1 | 1, A[i]);
			T[i << 1 | 1].eb(i << 1, -A[i]);
		}
		for(auto y : G[i])
			if(ok1[y] && ok2[y])
				T[i << 1 | 1].eb(y << 1, 0), T[y << 1].eb(i << 1 | 1, 0);
	} rep(i, 1, n << 1 | 1) dis[i] = -1;
	dfs(2, 0); if(dis[n << 1 | 1] != -1) ans = __gcd(ans, dis[n << 1 | 1]);
	rep(i, 3, n << 1 | 1) if(dis[i] == -1) dfs(i, 0);
	if(ans < 0) ans = -ans; if(ans == 0) ans = -1; cout << ans << endl;
	return 0;
}
