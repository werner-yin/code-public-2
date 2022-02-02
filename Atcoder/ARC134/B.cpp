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

char s[N], t[N];
int pos[30], nxt[N][30], n;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; scanf("%s", s + 1);
	rep(i, 0, 25) pos[i] = n + 1;
	per(i, n, 1) {
		rep(j, 0, 25) nxt[i][j] = pos[j];
		pos[s[i] - 'a'] = i;
	} int cur = n;
	rep(i, 1, n) t[i] = s[i];
	rep(i, 1, n) {
		int lower = 30, x = s[i] - 'a';
		if(i > cur) break;
		rep(j, 0, x - 1) if(nxt[i][j] <= cur) { lower = j; break; }
		if(lower != 30) {
			while(s[cur] != lower + 'a') cur--;
			swap(t[i], t[cur]); cur--;
		}
	} printf("%s", t + 1);
	return 0;
}
