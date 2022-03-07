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
const int mod = 998244353;

int f[N][11], n;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, 9) f[1][i] = 1;
	rep(i, 2, n) {
		rep(j, 1, 9) if(f[i - 1][j]) {
			rep(t, -1, 1) if(j + t > 0 && j + t < 10) {
				(f[i][j + t] += f[i - 1][j]) %= mod;
			}
		}
	} int ans = 0;
	rep(i, 1, 9) (ans += f[n][i]) %= mod;
	cout << ans << endl;
	return 0;
}
