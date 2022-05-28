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

const int N = 110;

string s[N];
int dis[N][N], h, w, c[N][N];

bool init(int x, int y) { return x >= 0 && x < h && y >= 0 && y < w; }

queue < pii > q;

const pii H[] = { { 1, 0 }, { -1 , 0 }, { 0, 1 }, { 0, -1 } };

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	h = in, w = in; memset(dis, 0, sizeof dis);
	rep(i, 0, h - 1) cin >> s[i]; int tot = 0;
	rep(i, 0, h - 1) rep(j, 0, w - 1) if(s[i][j] == 'o') dis[i][j] = 1, q.ep(i, j), c[i][j] = ++tot;
	while(q.size()) {
		int x, y; tie(x, y) = q.front(); q.pop();
		//cerr << x << " " << y << " " << dis[x][y] << endl;
		for(auto v : H) {
			int nx = x + v.fi, ny = y + v.se;
			if(init(nx, ny)) {
				if(!dis[nx][ny]) dis[nx][ny] = dis[x][y] + 1, c[nx][ny] = c[x][y], q.ep(nx, ny);
				else if(c[nx][ny] != c[x][y]) return printf("%d\n", dis[nx][ny] + dis[x][y] - 1), 0;
			}
		}
	}
	return 0;
}
