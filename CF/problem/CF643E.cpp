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

const int N = 5e5 + 10;
const int K = 62;

db f[N][K + 10];
int n, fa[N], tot;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, K) f[1][i] = 1; tot = 1;
	while(n--) {
		int op = in, x = in;
		if(op == 1) {
			++tot; rep(i, 1, K) f[tot][i] = 1; fa[tot] = x;
			vec pot; x = tot; rep(i, 1, K + 1) { pot.eb(x), x = fa[x]; if(x == 0) break; }
			per(i, pot.size() - 1, 2) f[pot[i]][i] /= (f[pot[i - 1]][i - 1] + 1) / 2;
			rep(i, 1, pot.size() - 1) f[pot[i]][i] *= (f[pot[i - 1]][i - 1] + 1) / 2;
		} else {
			db ans = K - 1; rep(i, 1, K - 1) ans -= f[x][i];
			printf("%.7lf\n", ans);
		}
	}
	return 0;
}
