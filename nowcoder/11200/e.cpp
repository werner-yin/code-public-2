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

int n, m, d, dep[N], lstans, ch[N][2], vch[N][2], vfa[N], siz[N], ls, pos[N];
char s[N];

int dfs(int x, int lst, int p) {
	if(!x) return 0; vfa[x] = lst; pos[x] = p;
	if(!ch[x][0] && !ch[x][1]) return siz[x] = 1, x;
	if(x == 1 || (ch[x][0] && ch[x][1])) lst = x; 
	int p1 = dfs(ch[x][0], lst, lst == x ? 0 : p), p2 = dfs(ch[x][1], lst, lst == x ? 1 : p);
	if(lst != x) return p1 | p2;
	siz[x] = siz[p1] + siz[p2]; vch[x][0] = p1, vch[x][1] = p2; return x;
}

void tdfs(int x, int lst, int p) {
	if(!x) return; if(vfa[x] != vfa[lst]) return;
	if(x ^ lst) vfa[x] = lst, pos[x] = p;
	if(siz[x]) vch[lst][p] = x;
	tdfs(ch[x][0], lst, x == lst ? 0 : p), tdfs(ch[x][1], lst, x == lst ? 1 : p);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, d = in; 
	dep[1] = 1; rep(i, 2, n) { int x = in, y = in; ch[x][y] = i; dep[i] = dep[x] + 1; }
	dfs(1, 0, 0);
	int qcnt = 0, mcnt = 0;
	while(m--) {
		int op = in, x = in ^ lstans; 
		if(op == 1) {
			scanf("%s", s + 1); ls = strlen(s + 1); int p = x; ++mcnt;
			rep(i, 1, ls) {
				int v = s[i] - '0'; ch[p][v] = ++n;
				dep[ch[p][v]] = dep[p] + 1, p = ch[p][v]; vfa[p] = vfa[x]; 
			} siz[p]++;
			tdfs(x, x, -1); vch[vfa[x]][pos[x]] = x;
			p = x; while(p) siz[p] = siz[vch[p][0]] + siz[vch[p][1]], p = vfa[p];
		} else {
			int k = in, lst = 0; assert(k <= siz[1]); qcnt++;
			if(!siz[x]) x = vch[vfa[x]][pos[x]]; 
			while(siz[x] < k) lst = x, x = vfa[x];
			if(lst) { k -= siz[lst]; if(lst == vch[x][0]) x = vch[x][1]; else x = vch[x][0]; }
			while(dep[x] < d) {
				if(siz[vch[x][0]] >= k) x = vch[x][0];
				else k -= siz[vch[x][0]], x = vch[x][1];
			} printf("%d\n", lstans = x);
		}
	}
	return 0;
}
