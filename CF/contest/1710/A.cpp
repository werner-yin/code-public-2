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

int n, m, K;
int a[N], b[N];

bool check(int t, int v) {
	ll tot = 0; rep(i, 1, K) b[i] = a[i] / t, tot += b[i] >= 2 ? b[i] : 0;
	bool fl = tot >= v; if(!fl) return 0;
	sort(b + 1, b + K + 1, greater < int >());
	tot = 0; bool hav = 0; fl = 0;
	rep(i, 1, K) {
		int val = b[i] >= 2 ? b[i] : 0;
		tot += val; if(i * 2 <= v && tot >= v) fl = true;
	}
	return fl;
}

void solve() {
	n = in, m = in, K = in;
	rep(i, 1, K) a[i] = in;
	//fl &= 2 * K <= m;
	bool fl = check(n, m) || check(m, n);
	puts(fl ? "Yes" : "No");
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
