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

const int N = 3010;

int f[N][N], sf[N][N], n, mod;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, mod = in; f[0][0] = 1;
	rep(i, 0, n)
		rep(j, 0, n) {
		if(i) (sf[i][j] += sf[i - 1][j]) %= mod; (f[i][j] += sf[i][j]) %= mod;
		//cerr << i << " " << j << " " << f[i][j] << endl;
		if(!f[i][j]) continue;
		rep(dt, 1, 4) {
			int l = i + pow(10, dt - 1), r = i + pow(10, dt);
			chkmin(r, n + 1); if(l > r) break;
			(sf[l][1 + j + dt] += (25ll + (i == 0)) * f[i][j] % mod) %= mod;
			(sf[r][1 + j + dt] += mod - (25ll + (i == 0)) * f[i][j] % mod) %= mod;
		}
	} int ans = 0; rep(i, 0, n - 1) (ans += f[n][i]) %= mod;
	cout << ans << endl;
	return 0;
}
