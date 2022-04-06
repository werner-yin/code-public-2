#include <bits/stdc++.h>

#define in read<int>()
#define fi first
#define se second
#define eb emplace_back
#define rep(i, x, y) for(int i = (x); i <= (y); i++)

using namespace std;

using ll = long long;
using pii = pair < int, int >;
using veg = vector < pii >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x < y ? y : x; }

const int N = 1e6 + 10;

int n, sa[N], rk[N], ht[N], fa[N], indeg[N];
veg R[N];
char s[N];

int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }
void merge(int x, int y) {
	if(x > y) swap(x, y);
	for(int i = gf(x); i < y; i = gf(i)) fa[i] = gf(i + 1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("hush.in", "r", stdin); freopen("hush.out", "w", stdout);
#endif
	n = in; rep(i, 1, n) sa[i] = in, rk[sa[i]] = i;
	rep(i, 2, n) ht[i] = in;
	rep(i, 1, n) fa[i] = i;
	int j = 0;
	rep(i, 1, n) {
		if(j) j--; 
		while(j < ht[rk[i]])
			merge(rk[i + j], rk[sa[rk[i] - 1] + j]), j++;
	} 
	rep(i, 2, n)
		if(~ht[i]) {
			int p1 = sa[i - 1] + ht[i], p2 = sa[i] + ht[i];
			if(p1 > n || p2 > n) continue;
			R[gf(rk[p2])].eb(gf(rk[p1]), 1);// cerr << p1 << " " << p2 << endl;
		} else {
			int p1 = sa[i - 1], p2 = sa[i];
			if(rk[sa[i - 1] + 1] > rk[sa[i] + 1]) R[gf(rk[p2])].eb(gf(rk[p1]), 1);
			else R[gf(rk[p2])].eb(gf(rk[p1]), 0);
		}
	rep(x, 1, n) if(gf(x) == x) {
		char mx = 'a';
		for(auto v : R[x]) chkmax(mx, (char)(s[v.fi] + v.se));
		s[x] = mx;
	}
	rep(i, 1, n) s[i] = s[gf(i)];
	rep(i, 1, n) putchar(s[rk[i]]); puts(""); return 0;
}
