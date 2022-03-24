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

ll dis[N], L, R;
int n, a[N];
bool vis[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, L = lin, R = lin; rep(i, 1, n) a[i] = in;
	rep(i, 2, n) if(a[i] < a[1]) swap(a[i], a[1]);
	memset(dis, 0x3f, sizeof dis); dis[0] = 0; priority_queue < pair < ll, int >, vector < pair < ll, int > >, greater < pair < ll, int > >> q;
	q.ep(dis[0], 0);
	while(q.size()) {
		int x = q.top().se, y; q.pop(); if(vis[x]) continue; vis[x] = true;
		rep(i, 2, n) if(dis[y = (x + a[i]) % a[1]] > dis[x] + a[i]) 
			dis[y] = dis[x] + a[i], q.ep(dis[y], y);
	}
	auto calc = [](ll x) {
					ll res = 0;
					rep(i, 0, a[1] - 1) 
						if(dis[i] <= x) res += (x - dis[i]) / a[1] + 1;
					return res;
				};
	printf("%lld\n", calc(R) - calc(L - 1));
	return 0;
}
