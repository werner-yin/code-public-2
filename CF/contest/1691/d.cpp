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

int n, a[N], lg[N];
pii st[20][N];
bool fl;

struct node {
	ll s, pre, suf;
};

pii getmax(int l, int r) {
	int k = lg[r - l + 1];
	return max(st[k][l], st[k][r - (1 << k) + 1]);
}

node check(int l, int r) {
	if(l > r) return node{ 0, 0, 0 };
	if(l == r) return (node){ a[l], max(a[l], 0), max(a[l], 0) }; int p = getmax(l, r).se;
	node ls = check(l, p - 1), rs = check(p + 1, r);
	node ret; ret.s = ls.s + rs.s + a[p]; ret.pre = max(ls.pre, ls.s + a[p] + rs.pre); ret.suf = max(rs.suf, rs.s + a[p] + ls.suf);
	fl |= ls.suf + rs.pre + a[p] > a[p]; return ret;
}

void solve() {
	n = in; rep(i, 1, n) a[i] = in;
	rep(i, 1, n) st[0][i] = { a[i], i };
	rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
	rep(i, 1, lg[n])
		rep(j, 1, n - (1 << i) + 1)
		st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
	fl = 0; check(1, n);
	puts(fl ? "NO" : "YES");
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
