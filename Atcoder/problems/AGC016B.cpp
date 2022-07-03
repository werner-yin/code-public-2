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

int n, a[N], cnt[N];

void check(int x) {
	int tot = 0, vtot = 0;
	rep(i, 1, n) {
		if(a[i] == x) ++tot;
		else ++vtot;
	}
	int l = tot + (vtot > 0), r = tot + vtot / 2;
	if(x + 1 >= l && x + 1 <= r) {
		puts("Yes"); exit(0);
	}
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in, ++cnt[a[i]];
	rep(i, 0, n) if(cnt[i] + cnt[i + 1] == n) check(i);
	puts("No"); return 0;
}
