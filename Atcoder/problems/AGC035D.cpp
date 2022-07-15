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
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, a[N], U, m, cnt;

map < pii, ll > f[20][20];

ll dfs(int l, int r, int pl, int pr) {
	if(l > r) return 0;
	if(f[l][r].count(pii{ pl, pr })) return f[l][r][pii{ pl, pr }];
	++cnt; //cerr << "!" << l << " " << r << " " << pl << " " << pr << endl;
	ll &ret = f[l][r][pii{ pl, pr }]; ret = inf;
	rep(i, l, r)
		chkmin(ret, dfs(l, i - 1, pl, pl + pr) + dfs(i + 1, r, pl + pr, pr) + 1ll * a[i] * (pl + pr));
	return f[l][r][{ pl, pr }] = ret;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in;
	cout << dfs(2, n - 1, 1, 1) + a[1] + a[n] << endl;
	//cerr << "!" << cnt << endl;
	return 0;
}
