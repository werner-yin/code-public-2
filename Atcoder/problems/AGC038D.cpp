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

int n, m, q;
int fa[N], x[N], y[N], z[N], siz[N];

int gf(int x) { return x == fa[x] ? x : fa[x] = gf(fa[x]); }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, q = in;
	rep(i, 1, n) fa[i] = i, siz[i] = 1;
	auto merge = [&](int x, int y) {
		x = gf(x), y = gf(y);
		if(x == y) return; fa[x] = y; siz[y] += siz[x];
	};
	rep(i, 1, q) {
		x[i] = in + 1, y[i] = in + 1, z[i] = in;
		if(!z[i]) merge(x[i], y[i]);
	} int ct = 0;
	rep(i, 1, q)
		if(z[i]) {
			ct++;
			if(gf(x[i]) == gf(y[i])) return puts("No"), 0;
		}
	int tot = 0;
	rep(i, 1, n) if(gf(i) == i) tot++;
  	if(m < n - 1) return puts("No"), 0;
	if(!ct) {
		puts(m >= 1ll * tot * (tot - 1) / 2 + n - tot + 1? "No" : "Yes");
	} else {
		cerr << tot << endl;
		if(tot == 2) return puts("No"), 0;
		if(m == n - 1) return puts("No"), 0;
		if(m >= 1ll * tot * (tot - 1) / 2 + n - tot + 1) return puts("No"), 0;
		puts("Yes");
	}
	return 0;
}
