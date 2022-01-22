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
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) >> 1;

int n, m, K;
struct node {
	db val; ll res;
};
node operator + (node a, node b) { return (node) { a.val + b.val, (a.res + b.res) % mod }; }
node operator - (node a, node b) { return (node) { a.val - b.val, (a.res - b.res + mod) % mod }; }
node operator / (node a, int b) { if(b == 2) return (node) { (a.val) / 2, 1ll * a.res * inv2 % mod }; assert(0); }

node f[2010][2010];
bool vis[2010][2010];

node dfs(int x, int y) {
	if(x == y) return (node){ 1ll * K * x, 1ll * K * x % mod };
	if(y == 0) return dfs(x - 1, y);
	if(vis[x][y]) return f[x][y]; vis[x][y] = true;
	auto a = dfs(x - 1, y - 1), b = dfs(x - 1, y); // a : add, b : -
	if(a.val > b.val) return f[x][y] = b;
	else return f[x][y] = a + (b - a) / 2;
}

void solve() {
	n = in, m = in, K = in;
	rep(i, 0, n) rep(j, 0, m) vis[i][j] = 0;
	cerr << dfs(n, m).val << endl;
	printf("%lld\n", dfs(n, m).res);
}

int main() {
#ifndef ONLINE_JUDGE
	//	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();	
	return 0;
}
