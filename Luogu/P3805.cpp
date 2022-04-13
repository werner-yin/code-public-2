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

const int N = 3e7 + 10;

char s[N], t[N];
int n, tot, p[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", s + 1); n = strlen(s + 1);
	t[tot = 1] = '?'; t[++tot] = '#'; rep(i, 1, n) t[++tot] = s[i], t[++tot] = '#';
	t[++tot] = '!';
	int r = 0, pos = 0, ans = 0;
	rep(i, 1, tot) {
		if(i <= r) p[i] = min(r - i + 1, p[2 * pos - i]);
		while(t[p[i] + i] == t[i - p[i]]) p[i]++;
		if(i + p[i] - 1 >= r) r = i + p[i] - 1, pos = i;
		chkmax(ans, p[i] - 1);
	} printf("%d\n", ans);
	return 0;
}
