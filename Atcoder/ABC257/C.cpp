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

int n, ans, ret;
char s[N];
int id[N], w[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; scanf("%s", s + 1);
	rep(i, 1, n) w[i] = in, id[i] = i;
	sort(id + 1, id + n + 1, [&](int x, int y) { return w[x] < w[y]; });
	int ret = 0; rep(i, 1, n) ret += s[i] == '1'; chkmax(ans, ret);
	rep(i, 1, n) {
		if(s[id[i]] == '1') ret--;
		else ret++;
		if(i == n || w[id[i]] != w[id[i + 1]]) chkmax(ans, ret);
	} cout << ans << endl;
	return 0;
}
