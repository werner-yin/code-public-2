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

int n, m, cnt[N], a[N];
int dt[N], ans;

void add(int x) {
	int v = x - cnt[x]; cnt[x]++;
	if(v > 0) {
		if(dt[v] == 0) ans++;
		dt[v]++;
	}
}
void del(int x) {
	cnt[x]--; int v = x - cnt[x];
	if(v > 0) {
		if(dt[v] == 1) ans--;
		dt[v]--;
	}
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, n) a[i] = in, add(a[i]);
	while(m--) {
		int x = in, y = in;
		del(a[x]), a[x] = y, add(a[x]); printf("%d\n", n - ans);
	}
	return 0;
}
