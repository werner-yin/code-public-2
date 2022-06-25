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

int n, m, dis[3][N];
bool hav[N];
vec G[N];

void runit(int *dis, int s) {
	dis[s] = 0; queue < int > q; q.ep(s);
	while(q.size()) {
		int x = q.front(); q.pop();
		for(auto y : G[x]) if(dis[y] > dis[x] + 1) dis[y] = dis[x] + 1, q.ep(y);
	}
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 1, m) {
		int u = in, v = in;
		if(u == 0) hav[v] = true;
		else G[u].eb(v), G[v].eb(u);
	}
	memset(dis, 0x3f, sizeof dis);
	runit(dis[1], 1);
	runit(dis[2], n);
	int mnp1 = 1e9, mnp2 = 1e9;
	rep(i, 1, n) if(hav[i]) chkmin(mnp1, dis[1][i]);
	rep(i, 1, n) if(hav[i]) chkmin(mnp2, dis[2][i]);
	rep(i, 1, n) {
		int ans = dis[1][n];
		chkmin(ans, dis[1][i] + mnp2 + 1);
		chkmin(ans, dis[2][i] + mnp1 + 1);
		chkmin(ans, mnp1 + mnp2 + 2);
		if(ans > 1e8) ans = -1; printf("%d " , ans);
	} puts("");
	return 0;
}
