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

vec G[N];
int n, f[N][3];

void dfs(int x) {
	if(!G[x].size()) { f[x][1] = f[x][0] = 1; return; }
	f[x][0] = 1; 
	for(auto y : G[x]) {
		dfs(y);
		int link = (f[y][1] + f[y][2]) % mod;
		int cut  = (f[y][0] + f[y][2]) % mod;
		f[x][2] = (1ll * f[x][2] * (link + cut) % mod + 1ll * f[x][1] * link % mod) % mod;
		f[x][1] = (1ll * f[x][0] * link % mod + 1ll * f[x][1] * cut % mod) % mod;
		f[x][0] = 1ll * f[x][0] * cut % mod;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) G[in].eb(i);
	dfs(1); printf("%d\n", (f[1][0] + f[1][2]) % mod);
	return 0;
}
