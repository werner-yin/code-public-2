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

int n, m;
int a[N], b[N], c[N], d[N];
veg G[N];
bool vis[N], evis[N];

void dfs(int x) {
	vis[x] = true;
	for(auto v : G[x]) {
		int y = v.fi, id = v.se;
		if(evis[id]) continue;
		evis[id] = true; c[id] = x, c[id] = y;
		if(!vis[y]) dfs(y);
	}
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, m) a[i] = in; rep(i, 1, m) b[i] = in;
	rep(i, 1, m) {
		G[a[i]].eb(b[i], i);
		G[b[i]].eb(a[i], i);
	}
	rep(i, 1, n) if(!vis[i]) dfs(i);
	rep(i, 1, m) if(c[i] != a[i]) putchar('1'); else putchar('0');
	return 0;
}
