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

int n, h;
int deg[N];
vec G[N];
bool fl, vis[N];

void dfs(int x) {
	fl |= deg[x] != 0; vis[x] = true;
	for(auto y : G[x]) if(!vis[y]) dfs(y);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, h = in;
	rep(i, 1, n) {
		int a = in, b = in, c = in, d = in;
		int x, y;
		if(c == 0) x = a;
		else x = c + h;
		if(d == 0) y = b + h;
		else y = d;
		deg[x]++, deg[y]--; G[x].eb(y); G[y].eb(x);
	} rep(i, 1, h) if(deg[i] < 0) return puts("NO"), 0;
	rep(i, h + 1, h + h) if(deg[i] > 0) return puts("NO"), 0;
	//cerr << "!" << endl;
	rep(i, 1, h + h) if(!vis[i] && G[i].size()) {
		fl = 0, dfs(i);
		if(!fl) return puts("NO"), 0;
	} puts("YES");
	return 0;
}
