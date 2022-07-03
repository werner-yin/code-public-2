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

int n, a[N][N];
ll ans;
char s[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) rep(j, 1, n) scanf("%1d", &a[i][j]);
	rep(i, 1, n) rep(j, 1, n) {
		rep(tx, -1, 1)
			rep(ty, -1, 1) if(tx || ty) {
			int ci = i, cj = j;
			ll ret = 0;bool fl = 1;
			rep(k, 1, n) {
				ret = ret * 10 + a[ci][cj];
				ci += tx; cj += ty;
				if(ci == n + 1) ci = 1; if(cj == n + 1) cj = 1;
				if(ci == 0) ci = n; if(cj == 0) cj = n;
				fl = 0;
			}
			chkmax(ans, ret);
		}
	}
	cout << ans << endl;
	return 0;
}
