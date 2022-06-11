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

int n, E, T, x[N];
ll f[N], tf[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, E = in, T = in; rep(i, 1, n) x[i] = in;
	f[0] = 0; tf[0] = 1e18;
	rep(i, 1, n) {
		f[i] = 1e18;
		//rep(j, 1, i)
		//	chkmin(f[i], f[j - 1] + max(T, (x[i] - x[j]) * 2));
		int p = lower_bound(x + 1, x + i + 1, x[i] - T / 2) - x;
		chkmin(f[i], f[p - 1] + max(2 * (x[i] - x[p]), T));
		chkmin(f[i], tf[p - 1] + x[i] * 2);
		tf[i] = min(tf[i - 1], f[i - 1] - x[i] * 2);
		//cerr << i << " " << p << " " << f[i] << " " << tf[i] << endl;
	}
	cout << f[n] + E << endl;
	return 0;
}
