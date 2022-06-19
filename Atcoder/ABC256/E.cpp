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

bool vis[N];
int n, x[N], c[N], deg[N];
ll ans;
priority_queue < pii, vector < pii >, greater < pii > > tq;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) x[i] = in, deg[x[i]]++;
	rep(i, 1, n) c[i] = in;
	rep(i, 1, n) tq.ep(c[i], i);
	queue < int > q; rep(i, 1, n) if(!deg[i]) q.ep(i);
	rep(i, 1, n) {
		if(!q.size()) {
			while(vis[tq.top().se]) tq.pop();
			q.ep(tq.top().se); ans += tq.top().fi; tq.pop();
		} int x = q.front(); q.pop(); deg[x] = 0;
		vis[x] = true; if(!--deg[::x[x]]) q.push(::x[x]);
	} cout << ans << endl;
	return 0;
}
