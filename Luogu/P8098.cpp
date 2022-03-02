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

const int N = 1e5 + 10;

vec G[N];
int n, val[N], d[N], tim, K;

void dfs(int x) {
	reverse(G[x].begin(), G[x].end()); val[x] = --tim;
	for(auto y : G[x]) d[y] = d[x] + 1, dfs(y);
}

int main() {
#ifndef ONLINE_JUDGE
	//	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) 
		G[in + 1].eb(i);
	tim = n + 2; dfs(n + 1);
	printf("%d\n", K = n + 2);
	rep(i, 1, n) printf("%lld\n", 1ll * (d[1] - d[i]) * K + val[i]);
	return 0;
}
