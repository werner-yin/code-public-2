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

int indeg[N], n, m, stk[N], top;
vec G[N];

void dfs(int x) {
	while(G[x].size()) { int y = G[x].back(); G[x].pop_back(); dfs(y); }
	stk[++top] = x;
}

int S, T;
	
int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	while(m--) { int u = in, v = in; G[u].eb(v); indeg[v]++; }
	rep(x, 1, n) sort(G[x].begin(), G[x].end(), greater < int >());
	rep(i, 1, n)
		if(indeg[i] != G[i].size()) {
			if(int(indeg[i]) - G[i].size() == 1 && !T) T = i;
			else if(G[i].size() - int(indeg[i]) == 1 && !S) S = i;
			else return puts("No"), 0;
		}
	if(!S && !T) S = T = 1; else if(S && T); else if(S || T) return puts("No"), 0;
	dfs(S); per(i, top, 1) printf("%d ", stk[i]); puts("");
	return 0;
}
