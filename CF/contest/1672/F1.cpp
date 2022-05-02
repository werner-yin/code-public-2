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

vec pot[N];
int id[N], a[N], n, b[N];

void dec(int v) {
	rep(i, 2, n) {
		if(!pot[id[i]].size()) return;
		swap(b[pot[id[i]].back()], b[v]), pot[id[i]].pop_back();
	}
}

void solve() {
	n = in; rep(i, 1, n) pot[i].clear(); rep(i, 1, n) a[i] = in, b[i] = id[i] = i, pot[a[i]].eb(i);
	sort(id + 1, id + n + 1, [&](int x, int y) { return pot[x].size() > pot[y].size(); });
	for(auto v : pot[id[1]]) dec(v);
	rep(i, 1, n) printf("%d ", a[b[i]]); puts("");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
