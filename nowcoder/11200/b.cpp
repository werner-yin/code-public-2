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

int n, m, k, x[N], y[N];

set < pair < db, db > > s;

void solve() {
	n = in, m = in, k = in; s.clear();
	rep(i, 1, k) x[i] = in, y[i] = in;
	rep(i, 1, k)
		rep(j, i + 1, k) {
		db t1 = x[i] + x[j], t2 = y[i] + y[j];
		t1 /= 2, t2 /= 2;
		pair < db, db > t = { t1, t2 };
		if(s.find(t) != s.end()) return printf("YES %.1lf %.1lf\n", t1, t2), void();
		s.insert(t);
	} puts("NO");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
