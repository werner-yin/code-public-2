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

struct node {
	int x, y;
	node(int _x = 0, int _y = 0) : x(_x), y(_y) { }
	friend node operator - (node a, node b) { return node(a.x - b.x, a.y - b.y); }
	friend ll operator ^ (node a, node b) { return 1ll * a.x * b.y - 1ll * b.x * a.y; }
} t[N];

int n, p[N], p1[N], p2[N], top1, top2;

void divide(int l, int r) {
	if(r - l <= 1) return;
	bool fl = ((t[p[r]] - t[p[l]]) ^ (t[p[l + 1]] - t[p[l]])) > 0;
	top1 = top2 = 0;
	rep(i, l + 2, r - 1) {
		if((((t[p[i]] - t[p[l]]) ^ (t[p[l + 1]] - t[p[l]])) > 0) != fl) p1[++top1] = p[i];
		else p2[++top2] = p[i];
	} p1[++top1] = p[l + 1]; rep(i, 1, top1) p[i + l] = p1[i]; 
	int mid = l + top1; rep(i, 1, top2) p[mid + i] = p2[i];
	divide(l, mid); divide(mid, r);
}

void solve() {
	n = in; rep(i, 1, n) p[i] = i, t[i].x = in, t[i].y = in;
	divide(1, n); rep(i, 1, n) printf("%d ", p[i]); puts("");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
