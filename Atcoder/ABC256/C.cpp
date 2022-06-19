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

int h[10], w[10], a[10][10];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	rep(i, 1, 3) h[i] = in;
	rep(i, 1, 3) w[i] = in;
	int ans = 0;
	rep(i, 1, 30) rep(j, 1, 30) rep(k, 1, 30) rep(d, 1, 30) {
		a[1][1] = i;
		a[1][2] = j;
		a[2][1] = k;
		a[2][2] = d;
		a[1][3] = h[1] - a[1][1] - a[1][2];
		a[2][3] = h[2] - a[2][1] - a[2][2];
		a[3][1] = w[1] - a[1][1] - a[2][1];
		a[3][2] = w[2] - a[1][2] - a[2][2];
		a[3][3] = h[3] - a[3][1] - a[3][2];
		if(a[3][3] != w[3] - a[1][3] - a[2][3]) continue;
		bool fl = 1;
		rep(x, 1, 3) rep(y, 1, 3) fl &= a[x][y] > 0;
		ans += fl;
	} cout << ans << endl;
	return 0;
}
