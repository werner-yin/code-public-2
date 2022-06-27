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

int n, indeg[N], a[N];
vec G[N], T[N];
char s[N];

void dfs(int x, int p) {
	for(auto y : G[x]) if(y ^ p) dfs(y, x);
	if((indeg[x] & 1) != a[x]) {
		if(!p) { puts("-1"), exit(0); } indeg[x]++, T[p].eb(x);
	} else if(p) T[x].eb(p), indeg[p]++;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	scanf("%s", s + 1); rep(i, 1, n) a[i] = s[i] == 'B';
	dfs(1, 0); priority_queue < int, vector < int >, greater < int > > q;
	rep(i, 1, n) if(!indeg[i]) q.ep(i);
	while(q.size()) {
		int x = q.top(); q.pop(); printf("%d ", x);
		for(auto y : T[x]) if(!--indeg[y]) q.ep(y);
	} puts("");
	return 0;
}
