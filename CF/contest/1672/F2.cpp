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

vec pot[N], tpot[N];
int id[N], a[N], n, b[N], p[N];
bool vis[N];

random_device tnd;
mt19937 rnd(tnd());

void solve() {
	n = in; rep(i, 1, n) pot[i].clear(); rep(i, 1, n) a[i] = in, id[i] = i, pot[a[i]].eb(i);
	sort(id + 1, id + n + 1, [&](int x, int y) { return pot[x].size() > pot[y].size(); });
	int ans = pot[id[1]].size(); rep(i, 1, n) b[i] = in;
	rep(i, 1, n) pot[i].clear();
	rep(i, 1, n) pot[b[i]].eb(i);
	rep(_, 1, 100) {
		rep(i, 1, n) tpot[i] = pot[i], shuffle(tpot[i].begin(), tpot[i].end(), default_random_engine(rnd()));
		rep(i, 1, n) 
			p[i] = tpot[a[i]].back(), tpot[a[i]].pop_back(), vis[i] = 0;
		int cur = 0;
		//rep(i, 1, n) cerr << p[i] << " ";
		rep(i, 1, n) if(!vis[i]) {
			int x = i; ++cur;
			while(!vis[x]) vis[x] = true, x = p[x];
		} cerr << cur << " " << ans << endl;
		if(cur > ans) return puts("WA"), void();
	} puts("AC");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
