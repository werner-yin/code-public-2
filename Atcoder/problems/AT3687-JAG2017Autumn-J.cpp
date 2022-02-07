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

const int N = 2e5 + 10;

int n, d[N], g[N];
ll sd[N], ans;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) d[i] = in, sd[i] = sd[i - 1] + d[i];
	rep(i, 1, n) g[i] = in;
	priority_queue < ll > q[2];
	rep(i, 1, n) {
		rep(_, 0, 1) {
			ll cost = sd[i] + g[i]; bool fl = false;
			if(q[0].size()) {
				cost -= q[0].top();
				if(cost < 0) {
					ans += cost; q[0].pop(); fl = true;
					q[0].ep(sd[i] + g[i]); q[1].ep(sd[i] - g[i] + cost);
				}
			} if(!fl) q[1].ep(sd[i] - g[i]);
		}
		ll cost = sd[i] - q[1].top(); ans += cost;
		q[1].pop(); q[0].ep(sd[i] + cost);
	} cout << ans << endl;
	return 0;
}
