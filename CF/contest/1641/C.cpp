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

int fa[N], n, q;
set < int > G[N];

int gf(int x) {
	return fa[x] == x ? x : fa[x] = gf(fa[x]);
}

void merge(int x, int y) {
	x = gf(x), y = gf(y); fa[x] = y;
	if(G[x].size() > G[y].size()) {
		swap(G[x], G[y]);
	}
	for(auto v : G[x]) G[y].ep(v);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, q = in; rep(i, 0, n + 5) fa[i] = i;
	while(q--) {
		int op = in;
		if(op == 0) {
			int l = in, r = in, tp = in;
			if(tp == 0)
				for(int x = gf(l - 1); x < r; x = gf(x + 1)) {
					//					cerr << x << " " << x + 1 << endl;
					merge(x, x + 1);
				}
			else {
				l = gf(l - 1); r = gf(r);
				G[r].ep(l);
			}
		} else {
			int x = in;
			if(gf(x - 1) == gf(x)) puts("NO");
			else if(G[gf(x)].size() && gf(*G[gf(x)].rbegin()) == gf(x - 1)) puts("YES");
			else puts("N/A");
		}
	}
	return 0;
}
