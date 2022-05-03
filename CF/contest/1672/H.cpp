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

int n, q, a[N], b[N];
char s[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, q = in; scanf("%s", s + 1);
	rep(i, 2, n) if(s[i] == s[i - 1]) (s[i] == '1' ? b : a)[i] = 1;
	rep(i, 1, n) a[i] += a[i - 1], b[i] += b[i - 1];
	while(q--) {
		int l = in, r = in, ans = max(a[r] - a[l], b[r] - b[l]) + 1;
		printf("%d\n", ans);
	}
	return 0;
}
