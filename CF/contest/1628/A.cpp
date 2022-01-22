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

int n, a[N], cnt[N], vcnt[N], rpos[N];

void solve() {
	n = in; rep(i, 1, n) a[i] = in;
	rep(i, 0, n) vcnt[i] = cnt[i] = rpos[i] = 0;
	rep(i, 1, n) cnt[a[i]]++;
	rep(i, 1, n) rpos[a[i]] = i;
	int MEX = 0; rep(i, 0, n) if(!cnt[i]) { MEX = i; break; }
	vec pot; int pos = 1, pcnt = 0, tpos = MEX;
	while(pos <= n) {
		map < int, bool > vis;
		int cmex = 0;
		while(pos <= n) {
			vis[a[pos]] = true; pos++;
			while(vis[cmex]) {
				cmex++;
			} if(cmex == MEX) break;
		} pot.eb(MEX);
		pcnt++; tpos = 0; while(rpos[tpos] >= pos) tpos++;
		MEX = tpos;
	} printf("%d\n", pot.size()); for(auto v : pot) printf("%d ", v); puts("");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
