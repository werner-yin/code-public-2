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

const int N = 5e5 + 10;
const int K = 22;

int b[N], a[N], id[N], n, ans[N], Q;
veg G[N];

void ins(int x, int vid) {
	per(i, K, 0)
		if(x >> i & 1) {
			if(vid > id[i]) 
				swap(b[i], x), swap(id[i], vid), x ^= b[i];
			else x ^= b[i];
		}
}

int query(int lim) {
	int ans = 0;
	per(i, K, 0)
		if(!(ans >> i & 1) && id[i] >= lim) ans ^= b[i];
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in;
	Q = in; rep(i, 1, Q) { int l = in, r = in; G[r].eb(l, i); }
	rep(i, 1, n) {
		ins(a[i], i);
		for(auto v : G[i]) ans[v.se] = query(v.fi); 
	} rep(i, 1, Q) printf("%d\n", ans[i]);
	return 0;
}
