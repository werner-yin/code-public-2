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

const int N = 110;

int n, T, L, u[N * N], v[N * N];

struct mat {
	bitset < N > t[N];
	friend mat operator * (mat a, mat b) {
		mat c;
		rep(i, 1, n) rep(j, 1, n) if(a.t[i].test(j)) {
			c.t[i] |= b.t[j];
		} return c;
	}
};


bool check(int lim, int x) {
	mat pre, cur; cur.t[1].set(1);
	rep(i, 1, lim) pre.t[u[i]].set(v[i]);
	for(int t = L; t; t >>= 1, pre = pre * pre)
		if(t & 1) cur = cur * pre;
	if(cur.t[1].test(x)) return true;
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, T = in, L = in;
	rep(i, 1, T) u[i] = in, v[i] = in;
	rep(i, 1, n) {
		int l = 1, r = T, ans = -1;
		while(l <= r) {
			int mid = l + r >> 1;
			if(check(mid, i)) ans = mid, r = mid - 1;
			else l = mid + 1;
		} printf("%d ", ans);
	} puts("");
	return 0;
}
