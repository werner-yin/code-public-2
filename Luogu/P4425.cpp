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

const int N = 2e5 + 10;

int n, m, P;
int t[N], a[N];
int val[N << 2], mx[N << 2];

int solve(int o, int l, int r, int x) {
	if(l == r) return l + max(x, mx[o]);
	int mid = l + r >> 1;
	if(x >= mx[o << 1 | 1]) return min(solve(o << 1, l, mid, x), mid + 1 + x);
	else return min(val[o], solve(o << 1 | 1, mid + 1, r, x));
}

void pu(int o, int l, int r) {
	mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
	int mid = l + r >> 1; val[o] = solve(o << 1, l, mid, mx[o << 1 | 1]);
}

void build(int o = 1, int l = 1, int r = n * 2) {
	if(l == r) return val[o] = t[l], mx[o] = a[l], void(); int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); pu(o, l, r);
}

void upd(int pos, int o = 1, int l = 1, int r = n * 2) {
	if(l == r) return val[o] = t[l], mx[o] = a[l], void(); int mid = l + r >> 1;
	if(pos <= mid) upd(pos, o << 1, l, mid); else upd(pos, o << 1 | 1, mid + 1, r); pu(o, l, r);
}

int get() { return n - 1 + val[1]; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, P = in;
	rep(i, 1, n) t[i] = in, a[i] = t[i] - i, t[i + n] = t[i], a[i + n] = t[i + n] - i - n;
	build(); int ans; printf("%d\n", ans = get());
	rep(i, 1, m) {
		int x = in, y = in; if(P) x ^= ans, y ^= ans;
		t[x] = y; t[x + n] = y; a[x] = t[x] - x; a[x + n] = t[x] - x - n; upd(x); upd(x + n);
		printf("%d\n", ans = get());
	}
	return 0;
}
