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
const int B = 310;

int ans[N], cnt[N], a[N], n, Q, l[N], r[N], xl[N], id[N], res;

void add(int x) {
	cnt[a[x]]++;
	res += cnt[a[x]] % 2 == 0;
}

void del(int x) {
	cnt[a[x]]--;
	res -= cnt[a[x]] & 1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) a[i] = in;
	Q = in; rep(i, 1, Q) l[i] = in, r[i] = in, xl[i] = (l[i] - 1) / B + 1, id[i] = i;
	sort(id + 1, id + Q + 1, [](int x, int y) { return xl[x] ^ xl[y] ? xl[x] < xl[y] : xl[x] & 1 ? r[x] > r[y] : r[x] < r[y]; });
	int L = 1, R = 0;
	rep(i, 1, Q) {
		int x = id[i];
		while(R < r[x]) add(++R); while(R > r[x]) del(R--);
		while(L < l[x]) del(L++); while(L > l[x]) add(--L);
		ans[x] = res;
	} rep(i, 1, Q) printf("%lld\n", ans[i]);
	return 0;
}
