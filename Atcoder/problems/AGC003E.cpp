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

int n, Q;
ll a[N], cnt[N], dt[N], ans[N];
int top;

void solve(int x, ll t, ll pv) {
#ifdef YJR_2333_TEST
	cerr << x << " " << t << " " << pv << endl;
#endif
	if(t == 0) return;
	if(x == 0) return dt[1] += pv, dt[t + 1] -= pv, void(); 
	int p = lower_bound(a + 1, a + x + 1, t) - a - 1;
	return cnt[p] += t / a[p] * pv, solve(p, t % a[p], pv);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, Q = in; a[top = 0] = n;
	rep(i, 1, Q) { ll x = lin; while(top >= 0 && x <= a[top]) top--; a[++top] = x; }
	cnt[top] = 1;
	per(i, top, 1) if(cnt[i]) {
		cnt[i - 1] += a[i] / a[i - 1] * cnt[i];
		solve(i - 1, a[i] % a[i - 1], cnt[i]);
	}
	dt[1] += cnt[0]; dt[a[0] + 1] -= cnt[0];
	rep(i, 1, n) dt[i] += dt[i - 1], ans[i] += dt[i];
	rep(i, 1, n) printf("%lld\n", ans[i]);
	return 0;
}
