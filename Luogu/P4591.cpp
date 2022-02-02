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

const int N = 1e4 + 10;
const int mod = 1e9 + 7;

char s[N], t[N];
int nxt[N], f[2][N], n, K;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	K = in; scanf("%s", s + 1); n = strlen(s + 1);
	int o = 0; rep(i, 0, n) f[o][i] = 1;
	rep(_, 1, K) {
		int x = in; rep(j, 0, n) f[o ^ 1][j] = 0; 
		while(x--) {
			scanf("%s", t + 1);
			int m = strlen(t + 1);
			int j = 0; 
			rep(i, 2, m) {
				while(t[i] != t[j + 1] && j) j = nxt[j];
				if(t[i] == t[j + 1]) j++;
				nxt[i] = j;
			} j = 0;
			rep(i, 1, n) {
				while((j == m || s[i] != t[j + 1]) && j) j = nxt[j];
				if(s[i] == t[j + 1]) j++;
				if(j == m) f[o ^ 1][i] = (f[o ^ 1][i] + f[o][i - m]) % mod;
			}
		} o ^= 1;
	} int ans = 0; rep(i, 0, n) ans = (ans + f[o][i]) % mod;
	printf("%d\n", ans); return 0;
}