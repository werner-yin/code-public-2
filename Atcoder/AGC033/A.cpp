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

const int N = 1010;
const pii H[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

char s[N][N];
int h, w;
int dis[N][N], ans;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	h = in, w = in;
	rep(i, 1, h) scanf("%s", s[i] + 1);
	queue < pii > q; rep(i, 1, h) rep(j, 1, w) if(s[i][j] == '#') q.ep(i, j), dis[i][j] = 1;
	while(q.size()) {
		pii x = q.front(); q.pop(); chkmax(ans, dis[x.fi][x.se] - 1);
		for(auto v : H) {
			pii y; y.fi = x.fi + v.fi, y.se = x.se + v.se;
			if(y.fi < 1 || y.fi > h || y.se < 1 || y.se > w) continue;
			if(!dis[y.fi][y.se]) dis[y.fi][y.se] = dis[x.fi][x.se] + 1, q.ep(y);
		}
	} cout << ans << endl;
	return 0;
}
