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

int k, n, q, a[N], l[N];

bool vis[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, k = in, q = in; rep(i, 1, k) a[i] = in; rep(i, 1, q) l[i] = in;
	rep(i, 1, k) vis[a[i]] = true;
	rep(i, 1, q) {
		int x = l[i];
		if(a[x] == n) continue;
		if(vis[a[x] + 1]) continue;
		vis[a[x]] = false; vis[a[x] + 1] = true; a[x]++;
	} rep(i, 1, k) printf("%d ", a[i]); puts("");
	return 0;
}
