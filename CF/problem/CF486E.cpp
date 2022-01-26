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

const int N = 1e5 + 10;
const int mod = 1e9 + 7;
const int V = 1e5;

int a[N], n, len1[N], tcnt1[N], len2[N], tcnt2[N];

struct node {
	int mx, cnt;
} tr[N];

node operator + (node a, node b) {
	node c; c.mx = max(a.mx, b.mx); c.cnt = 0;
	if(a.mx == c.mx) c.cnt += a.cnt;
	if(b.mx == c.mx) c.cnt += b.cnt;
	c.cnt %= mod; return c;
}

void add1(int x, node v) {
	x++; for(; x; x -= x & -x) tr[x] = tr[x] + v;
}
node query1(int x) {
	x++; node res; res.mx = 0; res.cnt = 0;
	for(; x <= V + 2; x += x & -x) res = res + tr[x];
	return res;
}

void add2(int x, node v) {
	x++; for(; x <= V + 2; x += x & -x) tr[x] = tr[x] + v;
}
node query2(int x) {
	x++; node res; res.mx = 0; res.cnt = 0;
	for(; x; x -= x & -x) res = res + tr[x];
	return res;
}
void clear() { rep(i, 1, V + 2) tr[i].mx = tr[i].cnt = 0; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in;
	add2(0, (node){ 0, 1 });
	node ans = (node) { 0, 1 };
	rep(i, 1, n) {
		auto v = query2(a[i] - 1); v.mx++; ans = ans + v;
		len1[i] = v.mx; tcnt1[i] = v.cnt;
		add2(a[i], v);
	} 
	clear(); add1(V + 1, (node) { 0, 1 });
	per(i, n, 1) {
		auto v = query1(a[i] + 1); v.mx++;
		len2[i] = v.mx; tcnt2[i] = v.cnt;
		add1(a[i], v);
	}
	rep(i, 1, n) {
		if(len1[i] + len2[i] - 1 == ans.mx) {
			if(1ll * tcnt1[i] * tcnt2[i] % mod == ans.cnt) printf("%d", 3);
			else printf("%d", 2);
		} else printf("%d", 1);
	}
	return 0;
}
