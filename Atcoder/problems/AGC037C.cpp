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

int n, a[N], b[N];
ll ans;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in; rep(i, 1, n) b[i] = in;
	priority_queue < pii > q;
	rep(i, 1, n) if(b[i] > a[i]) q.ep(b[i], i);
	while(q.size()) {
		int x = q.top().se; q.pop();
		int cnt = (b[x] - a[x]) / (b[(x - 2 + n) % n + 1] + b[x % n + 1]);
		if(cnt == 0) return puts("-1"), 0;
		ans += cnt; b[x] -= cnt * (b[(x - 2 + n) % n + 1] + b[x % n + 1]);
		if(b[x] != a[x]) q.ep(b[x], x);
	} cout << ans << endl;
	return 0;
}
