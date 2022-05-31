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

vector < tuple < int, int, int > > pot;
int n, fa[N];
set < pii > tpot[2];

int gf(int x) { return x == fa[x] ? x : fa[x] = gf(fa[x]); }

void solve() {
	n = in; pot.clear(), tpot[0].clear(), tpot[1].clear(); rep(i, 1, n) { int c = in, l = in, r = in; pot.eb(l, r, c); }
	sort(pot.begin(), pot.end()); rep(i, 1, n) fa[i] = i; int tot = 0;
	for(auto v : pot) {
		int l, r, c, id = ++tot; tie(l, r, c) = v;
		auto it = tpot[c ^ 1].begin();
		while(it != tpot[c ^ 1].end()) {
			if(it->fi < l) tpot[c ^ 1].erase(it++);
			else it++;
		}
		if(tpot[c ^ 1].size()) {
			pii mxr = { 0, 0 };
			for(auto v : tpot[c ^ 1]) chkmax(mxr, v), fa[gf(v.se)] = gf(id);
			tpot[c ^ 1].clear(); tpot[c ^ 1].ep(mxr);
		}
		tpot[c].ep(r, id);
	}
	int ans = 0; rep(i, 1, n) if(gf(i) == i) ans++;
	printf("%d\n", ans);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
