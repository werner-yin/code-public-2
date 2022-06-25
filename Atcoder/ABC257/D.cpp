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

const int N = 210;

int n;
ll x[N], y[N], p[N];
ll dis[N][N];
bool vis[N];
queue < int > q;

bool can(int x, ll mid) {
	while(q.size()) q.pop(); q.ep(x); rep(i, 1, n) vis[i] = 0; vis[x] = 1;
	while(q.size()) {
		int x = q.front(); q.pop();
		rep(y, 1, n) if(dis[x][y] <= mid && !vis[y]) vis[y] = true, q.ep(y);
	}
	rep(i, 1, n) if(!vis[i]) return 0;
	return 1;
}

bool check(ll mid) {
	rep(i, 1, n) if(can(i, mid)) return true;
	return false;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) x[i] = in, y[i] = in, p[i] = in;
	rep(i, 1, n) rep(j, 1, n) dis[i][j] = (abs(x[i] - x[j]) + abs(y[i] - y[j]) + p[i] - 1) / p[i];
	ll l = 0, r = 1e10;
	while(l <= r) {
		ll mid = l + r >> 1;
		if(!check(mid)) l = mid + 1;
		else r = mid - 1;
	} cout << l << endl;
	return 0;
}
