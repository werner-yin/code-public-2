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

ll ret[N], n, a[N];
vec G[N];
bool fl = 0;

void dfs(int x, int p) {
	if(fl) return; vector < ll > pot; ll tot = 0, vtot;
	for(auto y : G[x]) if(y ^ p) dfs(y, x), pot.eb(ret[y]), tot += ret[y];
	if(G[x].size() == 1) return ret[x] = a[x], void();
	sort(pot.begin(), pot.end()); vtot = tot; ll mx = pot.back(); 
	ll delta = tot - a[x]; //cerr << x << " " << delta << " " << mx << endl;
	if(delta < 0) fl = 1;
  	if(tot - mx >= delta) ret[x] = tot - 2 * delta; else fl = 1;
  	if(delta * 2 > tot) fl = 1;
	//cerr << "!" << ret[x] << endl;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in;
	rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	if(n == 2) return puts(a[1] == a[2] ? "YES" : "NO"), 0;
	int rt = 0; rep(i, 1, n) if(G[i].size() != 1) rt = i;
	dfs(rt, 0); puts(!fl && !ret[rt]? "YES" : "NO");
	return 0;
}
