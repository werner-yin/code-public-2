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

const int N = 2e5 + 10;
const int LIM = 410;

int n, p[N], dep[N], tp[N], pri[N], pnum;
ll tans[N], ans[N], f[N], tf[N];
bool v[N];
vec G[N], g[N];

void init(int l) {
	rep(i, 2, l) {
		if(!v[i]) pri[++pnum] = i;
		rep(j, 1, pnum) {
			int t = pri[j] * i; if(t > l) break; v[t] = true;
			if(i % pri[j] == 0) break;
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) p[i] = in, tp[i] = i, dep[i] = dep[p[i]] + 1, tans[dep[i]]++;
	per(i, n, 1) tans[i] += tans[i + 1]; init(n);
	rep(x, 1, LIM) {
		rep(i, 0, n) f[i] = tf[i] = 0;
		per(i, n, 1) {
			f[i]++; tf[tp[i]] += f[i]; tp[i] = p[tp[i]]; ans[x] += tf[i] * f[p[i]];
			f[p[i]] += tf[i];
		}
	}
	per(i, n, 2) {
		g[i].eb(1);
		if(g[i].size() > g[p[i]].size()) swap(g[i], g[p[i]]);
		rep(x, LIM + 1, g[i].size()) {
			ll tot1 = 0, tot2 = 0;
			for(int t = x; t <= g[i].size(); t += x) tot1 += g[i][g[i].size() - t];
			for(int t = x; t <= g[p[i]].size(); t += x) tot2 += g[p[i]][g[p[i]].size() - t];
			ans[x] += tot1 * tot2;
		}
		for(int t = 0; t < g[i].size(); t++)
			g[p[i]][g[p[i]].size() - t - 1] += g[i][g[i].size() - t - 1];
	}
	//rep(i, 1, n) cerr << ans[i] << " "; cerr << endl;
	rep(i, 1, pnum)
		for(int j = 1; j <= n / pri[i]; j++)
			ans[j] -= ans[pri[i] * j];
	//rep(i, 1, n) cerr << ans[i] << " "; cerr << endl;
	rep(i, 1, n - 1) printf("%lld\n", ans[i] + tans[i]);
	return 0;
}
