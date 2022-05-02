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

const int N = 1010;

char s[N][N];
int a[N][N], lans[N][N], tot, ans, n, m, q;
veg al;
int id[N][N];

void upd(int x, int y) {
	int t = id[x][y] <= tot && !a[x][y];
	ans -= lans[x][y]; ans += t; lans[x][y] = t;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, q = in;
	rep(i, 1, n) scanf("%s", s[i] + 1);
	rep(i, 1, n) rep(j, 1, m) a[i][j] = s[i][j] == '*', tot += a[i][j];
	rep(i, 1, n) rep(j, 1, m) al.eb(j, i);
	sort(al.begin(), al.end()); int tim = 0;
	for(auto v : al) id[v.se][v.fi] = ++tim;
	rep(i, 1, n) rep(j, 1, m) upd(i, j);
	while(q--) {
		int x = in, y = in; int ltot = tot; tot -= a[x][y]; a[x][y] ^= 1; tot += a[x][y];
		upd(x, y); upd(al[max(ltot, tot) - 1].se, al[max(ltot, tot) - 1].fi); printf("%d\n", ans);
	}
	return 0;
}
