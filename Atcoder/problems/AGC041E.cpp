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

const int N = 5e4 + 10;
const int M = 1e5 + 10;

int n, m, T, x[M], y[M], to[N], cnt[N];
bitset < N > go[N];
char ans[M];
bool vis[N];
	
int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, T = in;
	rep(i, 1, m) x[i] = in, y[i] = in;
	if(T == 1) {
		rep(i, 1, n) go[i].set(i);
		rep(i, 1, m)
			go[x[i]] = go[y[i]] = go[x[i]] | go[y[i]];
		int pos = -1; rep(i, 1, n) if(go[i].count() == n) { pos = i; break; }
		if(pos == -1) return puts("-1"), 0;
		vis[pos] = 1;
		per(i, m, 1)
			if(vis[x[i]] == vis[y[i]]) ans[i] = '^';
			else if(vis[x[i]]) ans[i] = '^', vis[y[i]] = true;
			else ans[i] = 'v', vis[x[i]] = true;
		printf("%s\n", ans + 1);
	} else {
		if(n == 2) return puts("-1"), 0;
		rep(i, 1, n) to[i] = i, cnt[i] = 1;
		per(i, m, 1)
			if(cnt[to[x[i]]] == n - 1)
				cnt[to[x[i]]]--, to[x[i]] = to[y[i]], cnt[to[x[i]]]++, ans[i] = 'v';
			else cnt[to[y[i]]]--, to[y[i]] = to[x[i]], cnt[to[y[i]]]++, ans[i] = '^';
		printf("%s\n", ans + 1);
	}
	return 0;
}
