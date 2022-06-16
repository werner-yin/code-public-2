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

using pll = pair < ll, ll >;

pii ch[N][2];
int n;
vector < pll > f[N];

void dfs(int x, ll lim) {
	f[x].clear(); if(!x) return f[x].eb(0, 0), void();
	dfs(ch[x][0].fi, lim), dfs(ch[x][1].fi, lim);
	rep(tp, 0, 1) {
		int ls = ch[x][tp].fi, rs = ch[x][tp ^ 1].fi;
		int len = ch[x][tp].se + ch[x][tp ^ 1].se, pos = 0;
		for(int i = 0; i < f[ls].size(); i++) {
			while(pos + 1 < f[rs].size() && f[rs][pos + 1].fi + f[ls][i].se + len <= lim) pos++;
			if(pos < f[rs].size() && f[rs][pos].fi + f[ls][i].se + len <= lim)
				f[x].eb(f[ls][i].fi + ch[x][tp].se, f[rs][pos].se + ch[x][tp ^ 1].se);
		}
	}
	sort(f[x].begin(), f[x].end()); vector < pll > g;
	ll lst = 1e18; for(auto v : f[x]) if(v.se < lst) g.eb(v), lst = v.se;
	f[x].swap(g);
}

bool check(ll mid) { dfs(1, mid); return f[1].size(); }

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 2, n) {
		int p = in;
		ch[p][!!ch[p][0].fi] = { i, in }; 
	}
	ll l = 0, r = 0;
	rep(i, 1, n) r += ch[i][0].se + ch[i][1].se;
	while(l <= r) {
		ll mid = l + r >> 1;
		if(check(mid)) r = mid - 1;
		else l = mid + 1;
	} cout << l << endl;
	return 0;
}
