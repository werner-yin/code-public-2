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

int n, a[N], b[N], val;
map < int, int > cnt;
int fa[N], siz[N], ans;

int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }
void merge(int x, int y) {
	x = gf(x), y = gf(y); if(x == y) return;
	fa[x] = y; siz[y] += siz[x];
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) a[i] = in, val ^= a[i], cnt[a[i]]++;
	rep(i, 1, n) b[i] = in, cnt[b[i]]--;
	cnt[val]++;
	for(auto v : cnt) if(v.se < 0) return puts("-1"), 0;
	int tot = 0; for(auto &v : cnt) v.se = ++tot;
	rep(i, 1, tot) fa[i] = i, siz[i] = 1;
	rep(i, 1, n) if(a[i] != b[i]) ++ans, merge(cnt[a[i]], cnt[b[i]]);
	rep(i, 1, tot) if(gf(i) == i && siz[gf(i)] > 1) ans++;
	if(siz[gf(cnt[val])] > 1) ans--;
	cout << ans << endl;
	return 0;
}
