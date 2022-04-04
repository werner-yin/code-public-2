#include <bits/stdc++.h>
#include <bits/extc++.h>

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define in read<int>()
#define lin read<ll>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;
using namespace __gnu_pbds;

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

using dt = tree<pii, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
	
int a[N], n, lg[N], pw[20];
pii mx[20][N];
ll ans;

pii getmx(int l, int r) { int k = lg[r - l + 1]; return max(mx[k][l], mx[k][r - pw[k] + 1]); }

void solve(int l, int r, dt &s) {
	if(l > r) return;
	int pos = getmx(l, r).se;
	dt ts; 
	if(pos - l >= r - pos) solve(l, pos - 1, s), solve(pos + 1, r, ts);
	else solve(l, pos - 1, ts), solve(pos + 1, r, s);
	for(auto v : ts) {
		int ret = a[pos] / v.fi;
		auto it = s.upper_bound(pii{ ret, n + 1 });
		if(it == s.end()) ans += s.size();
		else ans += s.order_of_key(*it);
	}
	for(auto v : ts) s.insert(v); 
	int ret = a[pos] / a[pos]; 
	auto it = s.upper_bound(pii{ ret, n + 1 });
	if(it == s.end()) ans += s.size();
	else ans += s.order_of_key(*it);
	s.insert({ a[pos], pos });
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in;
	rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
	rep(i, 1, n) mx[0][i] = pii{ a[i], i };
	pw[0] = 1; rep(i, 1, lg[n]) pw[i] = pw[i - 1] << 1;
	rep(i, 1, lg[n])
		rep(j, 1, n - pw[i] + 1) mx[i][j] = max(mx[i - 1][j], mx[i - 1][j + pw[i - 1]]);
	dt s; solve(1, n, s); rep(i, 1, n) ans += a[i] == 1; printf("%lld\n", ans);
	return 0;
}
