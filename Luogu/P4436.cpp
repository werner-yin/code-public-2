#include <bits/stdc++.h>

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define in read<int>()
#define lin read<ll>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)
#define lock RUBBISH_VAR

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

bool lock[N], vis[N];
int pos[N], L[N], R[N], n, m, p;

void dfs(int x) {
	if(vis[x]) return; vis[x] = true;
	while(L[x] > 1 || R[x] < n) {
		bool fl = false;
		if(L[x] > 1 && (!lock[L[x] - 1] || (pos[L[x] - 1] <= R[x] && pos[L[x] - 1] >= L[x])))
			dfs(L[x] - 1), chkmax(R[x], R[L[x] - 1]), chkmin(L[x], L[L[x] - 1]), fl = true;
		if(R[x] < n && (!lock[R[x]] || (pos[R[x]] >= L[x] && pos[R[x]] <= R[x])))
			dfs(R[x] + 1), chkmin(L[x], L[R[x] + 1]), chkmax(R[x], R[R[x] + 1]), fl = true;
		if(!fl) break;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, p = in;
	rep(i, 1, m) {
		int x = in, y = in;
		pos[x] = y; lock[x] = true;
	} rep(i, 1, n) L[i] = R[i] = i;
	rep(i, 1, n) dfs(i);
	while(p--) {
		int s = in, t = in;
		puts(L[s] <= t && R[s] >= t ? "YES" : "NO");
	}
	return 0;
}
