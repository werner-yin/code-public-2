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
const ll inf = 1e18;

int a[N], b[N], n;
bool vis[N];
ll ans;
vec pot;
vec G[N];

bool check(int s, int t) {
	rep(i, 0, 50) vis[i] = 0;
	vis[s] = true; queue < int > q; q.ep(s);
	while(q.size()) {
		int x = q.front(); q.pop();
		for(auto y : G[x]) if(!vis[y]) vis[y] = true, q.ep(y);
	} return vis[t];
}

bool check() {
	rep(i, 0, 50) G[i].clear();
	rep(i, 1, 50) for(auto v : pot) if(v <= i) G[i].eb(i % v);
	rep(i, 1, n) 
		if(!check(a[i], b[i])) return 0;
	return true;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in; rep(i, 1, n) b[i] = in;
	per(i, 51, 1) {
		vec lpot = pot;
		rep(j, 1, i - 1) pot.eb(j);
		if(!check()) {
			if(i == 51) return puts("-1"), 0;
			lpot.eb(i);
		}
		pot = lpot;
	} for(auto v : pot) ans |= 1ll << v;
	cout << ans << endl;
	return 0;
}
