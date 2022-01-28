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

#define fpos __FFPOS

const int N = 2e5 + 10;

int n, a[N], fpos[N], endpos[N];
ll tr[N];
void add(int x, int v) { for(; x <= n; x += x & -x) tr[x] += v; }
ll query(int x) { ll res = 0; for(; x; x -= x & -x) res += tr[x]; return res; }

void solve() {
	n = in; rep(i, 1, n) a[i] = in, (fpos[a[i]] == 0 && (fpos[a[i]] = i)), endpos[a[i]] = i;
	veg pot; rep(i, 1, n) if(endpos[i] - fpos[i] > 1) pot.eb(fpos[i], endpos[i]);
	//	cerr << pot.size() << endl;
	sort(pot.begin(), pot.end(), [](auto a, auto b) { return a.fi ^ b.fi ? a.fi < b.fi : a.se > b.se; });
	veg vpot; int lst = 0;
	for(auto v : pot) {
		if(v.se <= lst) continue;
		vpot.eb(v); lst = v.se;
	} //cerr << vpot.size() << endl;
	int ans = 0, dec = 0;
	//	for(auto v : vpot) cerr << v.fi << " " << v.se << endl;
	rep(i, 0, int(vpot.size()) - 1) {
		dec += 1 + (query(vpot[i].fi) == 0);
		add(vpot[i].fi, 1); add(vpot[i].se + 1, -1); 
		//		cerr << vpot[i].fi << " " << vpot[i].se << endl;
		int j = i + 1;
		while(j < vpot.size()) {
			if(vpot[j].fi > vpot[i].se) break;
			j++;
		} j--; i = max(i, j - 1);
	} rep(i, 1, n) if(query(i)) ans++;// , cerr << i << " " ;
	printf("%d\n", ans - dec);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = 1; T; T--) solve();
	return 0;
}
