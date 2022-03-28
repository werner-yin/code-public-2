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

const int N = 3e6 + 10;

int n, z[N], ans;
char s[N];
vec pot;

void zfunc() {
	z[1] = n; int p = 0, r = 0;
	rep(i, 2, n) {
		if(i <= r) z[i] = min(z[i - p + 1], r - i + 1);
		while(i + z[i] <= n && s[z[i] + i] == s[z[i] + 1]) z[i]++;
		if(i + z[i] - 1 >= r) r = i + z[i] - 1, p = i;
	}
}

int cmp(int x, int len) { // 1 < x ? only len char
	if(z[x] >= len) return 0;
	return s[x + z[x]] < s[z[x] + 1] ? -1 : 1;
}

int getmin(int x, int y, int i) { // assert(x > y);
	int t; assert(x > y);
	if(t = cmp(y + (i - x + 1), x - y)) return t == 1 ? x : y;
	if(t = cmp(x - y + 1, y - 1)) return t == 1 ? y : x;
	return y;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", s + 1); n = strlen(s + 1); zfunc();
	rep(i, 1, n) {
		vec tpot; tpot.eb(i); 
		for(auto v : pot) {
			while(tpot.size() && s[v + i - tpot.back()] < s[i]) tpot.pop_back();
			if(!tpot.size() || s[v + i - tpot.back()] == s[i]) {
				while(tpot.size() && 2 * (i - tpot.back() + 1) >= i - v + 1) tpot.pop_back();
				tpot.eb(v);
			}
		} pot = tpot; int ans = pot.front();
		for(auto v : pot) if(v != ans) ans = getmin(ans, v, i);
		printf("%d ", ans);
	} puts("");
	return 0;
}
