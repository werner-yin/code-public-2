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

int n, m, tim, tp[N], fa[N], a[N], b[N], tot, siz[N];
char s[114];
vector < tuple < int, int, int, int > > pot;
ll ret, cnt, ans[N];

int gf(int x) { return fa[x] == x ? x : gf(fa[x]); }

void merge(int x, int y, int w, int tid) {
	x = gf(x), y = gf(y); if(x == y) return;
	if(siz[x] > siz[y]) swap(x, y); pot.eb(x, y, w, tid); cnt++, ret += w; fa[x] = y; siz[y] += siz[x];
}

void undo() {
	int x, y, w, id; tie(x, y, w, id) = pot.back(); pot.pop_back();
	siz[y] -= siz[x]; fa[x] = x; cnt--, ret -= w;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 1, m) {
		scanf("%s", s + 1);
		if(s[1] == 'A') tp[i] = 0, a[i] = in, b[i] = in;
		else if(s[1] == 'D') tp[i] = 1, a[i] = in;
		else tp[i] = 2;
	} rep(i, 1, n) fa[i] = i, siz[i] = 1; 
	rep(i, 1, m) {
		if(tp[i] == 0) merge(a[i], b[i], i, ++tot), printf("%lld\n", ans[tot] = cnt == n - 1 ? ret : 0);
		else if(tp[i] == 1) {
			if(tp[i + 1] == 2) printf("%lld\n", ans[tot - a[i]]);
			else {
				while(pot.size() && get<3>(pot.back()) > tot - a[i]) undo();
				tot -= a[i]; printf("%lld\n", ans[tot] = cnt == n - 1 ? ret : 0);
			}
		} else if(tp[i] == 2) {
			if(pot.size() && get<2>(pot.back()) == i - 1) undo(); if(i > 1 && tp[i - 1] == 0) tot--;
			printf("%lld\n", ans[tot] = cnt == n - 1 ? ret : 0);
		} //cerr << "!" << cnt << " " << tp[i] << endl;
	}
	return 0;
}
