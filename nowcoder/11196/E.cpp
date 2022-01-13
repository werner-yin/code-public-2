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

const int N = 210;

bitset < N > a[N][N], b[N], c, tot;
int ans, n, m;

struct node {
	int a, b, c, d;
} val[100010];

bool operator < (node a, node b) { return a.a == b.a ? a.b == b.b ? a.c == b.c ? a.d > b.d : a.c < b.c : a.b < b.b : a.a < b.a; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; ans = n * n * n * n - m;
	rep(i, 1, m) val[i].a = in, val[i].b = in, val[i].c = in, val[i].d = in;
	sort(val + 1, val + m + 1);
	int cur = 1;
	rep(i, 1, n) {
		rep(k, 1, n) b[k].reset();
		rep(j, 1, n) {
			c.reset();
			rep(k, 1, n) {
				tot = (a[j][k] | b[k] | c); tot.flip();
				while(cur <= m && val[cur] < (node) { i, j, k, 0 }) {
					int p = tot._Find_next(val[cur].d);
					if(p <= n) a[j][k][p] = b[k][p] = c[p] = 1, ans--;
					p = val[cur].d; a[j][k][p] = b[k][p] = c[p] = 0;
					while(p <= n) tot[p] = 0, p++;
					cur++; 
				}
				int p = tot._Find_next(0);
				if(p <= n) a[j][k][p] = b[k][p] = c[p] = 1, ans--;
			}
		}
	} cout << ans << endl;
	return 0;
}
