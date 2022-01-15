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

const int N = 5e4 + 10;
const int B = 256;
const int U = B - 1;

int n, q, a[N], fa[N], dep[N], f[N][B + 10], lst[N];
vec G[N];
int ch[N << 5][2], ndn, mx[N][B + 10];

void ins(int x) {
	int p = 1;
	per(i, 7, 0) {
		int &v = ch[p][x >> i & 1];
		if(!v) v = ++ndn; p = v;
	}
}

int query(int val, int x) {
	int p = 1, res = 0, pos = 0;
	per(i, 7, 0) {
		int v = ~val >> i & 1;
		if(ch[p][v]) p = ch[p][v], res |= 1 << i;
		else p = ch[p][v ^= 1];
		pos |= v << i;
	} return mx[x][pos] | (res << 8);
}

void dfs(int x, int p) {
	dep[x] = dep[p] + 1; fa[x] = p;
	if(dep[x] >= B) {
		rep(i, 1, ndn) ch[i][0] = ch[i][1] = 0;
		ndn = 1;
		for(int y = x, d = 0; y && dep[x] - dep[y] < B; y = fa[y])
			lst[x] = y, chkmax(mx[x][a[y] >> 8], (a[y] xor d++) & U), ins(a[y] >> 8);
		rep(i, 0, U) f[x][i] = query(i, x); lst[x] = fa[lst[x]];
	} for(auto y : G[x]) if(y ^ p) dfs(y, x);
}

int qry(int x, int p) {
	int ans = 0, dis = 0;
	while(dep[x] - dep[p] >= B) 
		chkmax(ans, f[x][dis++]), x = lst[x];
	dis <<= 8;
	while(x ^ fa[p]) {
		chkmax(ans, dis xor a[x]); dis++; x = fa[x]; 
	} return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, q = in; rep(i, 1, n) a[i] = in;
	rep(i, 2, n) { int u = in, v = in; G[u].eb(v); G[v].eb(u); }
	dfs(1, 0); rep(i, 1, q) printf("%d\n", qry(in, in));
	return 0;
}
