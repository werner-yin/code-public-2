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

const int N = 5010;
const int M = 5e5 + 10;

int n, m, Q;
int w[N], u[M], v[M], fa[N];
char s[N];
bool vis[N][N];
vec G[N], T[N];

int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }

int col[N];
bool fl;

void dfs(int x, int c) {
	col[x] = c;
	for(auto y : T[x])
		if(!col[y]) G[x].eb(y), G[y].eb(x), dfs(y, 3 - c);
		else if(col[y] == c) fl = true;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, Q = in; scanf("%s", s + 1); rep(i, 1, n) w[i] = s[i] - '0';
	queue < pii > q; 
	rep(i, 1, m) {
		u[i] = in, v[i] = in;
		if(w[u[i]] == w[v[i]]) {
			T[u[i]].eb(v[i]), T[v[i]].eb(u[i]);
			q.ep(u[i], v[i]), vis[u[i]][v[i]] = vis[v[i]][u[i]] = true;
		}
	}
	rep(i, 1, n) if(!col[i]) {
		fl = 0; dfs(i, 2);
		if(fl) G[i].eb(i);
	} rep(i, 1, n) fa[i] = i;
	rep(i, 1, m) if(w[u[i]] != w[v[i]]) {
		int x = gf(u[i]), y = gf(v[i]);
		if(x != y) fa[x] = y, G[u[i]].eb(v[i]), G[v[i]].eb(u[i]);
	}
	rep(i, 1, n) q.ep(i, i), vis[i][i] = true;
	while(q.size()) {
		int x, y; tie(x, y) = q.front(); q.pop();
		for(auto tx : G[x])
			for(auto ty : G[y])
				if(!vis[tx][ty] && w[tx] == w[ty])
					vis[tx][ty] = vis[ty][tx] = true, q.ep(tx, ty);
	}
	while(Q--) {
		int x = in, y = in; puts(vis[x][y] ? "YES" : "NO");
	}
	return 0;
}
