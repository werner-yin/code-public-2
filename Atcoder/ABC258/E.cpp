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

int n, q;
ll w[N], s[N], tot, X;
int f[60][N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, q = in, X = lin;
	rep(i, 0, n - 1) w[i] = lin, s[i] = (i ? s[i - 1] : 0) + w[i], tot += w[i];
	ll vt = 1ll * X / tot * n; X %= tot; if(X == 0) X += tot, vt -= n;
	ll cur = 0; int pos = 0;
	rep(i, 0, n - 1) {
		while(cur + w[pos] < X) cur += w[pos], pos = (pos + 1) % n;
		f[0][i] = (pos + 1) % n;
		//cerr << i << " " << f[0][i] << " " << cur << endl;
		cur -= w[i];
	}
	rep(i, 1, 50) 
		rep(j, 0, n - 1) f[i][j] = f[i - 1][f[i - 1][j]];
	//int v = 0;
	//rep(i, 0, 100) v = f[0][v], cerr << v << endl;
	while(q--) {
		ll K = lin - 1;
		int pos = 0, i;
		per(i, 50, 0) if((1ll << i) <= K) pos = f[i][pos], K -= 1ll << i;
		i = pos, pos = f[0][pos];
		//cerr << "!" << i << " " << pos << endl;
		ll ans = pos > i ? pos - i : n - i + pos;
		ans += vt;
		printf("%lld\n", ans);
	}
	return 0;
}
