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
using ull = unsigned long long;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x > y ? x : y; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 1e6 + 10;
const ull base = 1e9 + 7;

int n, m;
int a[N][7], w[N], id[N], ans = 2e9 + 10;
ull val[N][40];
unordered_map < ull, int > mp;

void upd(int x, int v) {
	rep(i, 1, (1 << m) - 1) mp[val[x][i]] += v;
}

int query(int x) {
	int res = 0;
	rep(i, 1, (1 << m) - 1)
		res += mp[val[x][i]] * (__builtin_parity(i) ? 1 : -1);
	return res;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 1, n) {
		rep(j, 1, m) a[i][j] = in;
		sort(a[i] + 1, a[i] + m + 1);
		w[i] = in;
		rep(t, 1, (1 << m) - 1)
			rep(j, 1, m) if(t >> j - 1 & 1) val[i][t] = val[i][t] * base + a[i][j];
	}
	rep(i, 1, n) upd(id[i] = i, 1); 
	sort(id + 1, id + n + 1, [](auto a, auto b) { return w[a] < w[b]; });
	int pos = n;
	rep(i, 1, n) {
		if(pos <= i) break;
		upd(id[i], -1); bool fl = false; while(query(id[i]) < pos - i) fl = true, upd(id[pos], -1), pos--;
		if(fl) pos++, chkmin(ans, w[id[i]] + w[id[pos]]), upd(id[pos], 1);
	} if(ans > 2e9) ans = -1; printf("%d\n", ans);
	return 0;
}
