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

int n, K, a[N];
bool vis[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; if(K * 2 > n) return puts("-1"), 0;
	int l = -1, r = -1;
	rep(i, 1, n) {
		a[i] = i + K;
		if(a[i] > n) a[i] -= n;
		vis[a[i]] = true;
	}
	l = K + 1, r = K + K;
	chkmin(r, n - K);
	if(l <= r) {
		cerr << "!" << l << " "<< r << endl;
		rep(i, l, r)
			swap(a[i], a[n - K + i - l + 1]);
		bool fl = 0;
		rep(i, 1, n) if(abs(a[i] - i) < K) fl = 1;
		if(fl) {
			rep(i, l, r)
				swap(a[i], a[n - K + i - l + 1]);
		}
	}
	rep(i, 1, n) if(abs(a[i] - i) < K) return assert(0), puts("-1"), 0;
	rep(i, 1, n) assert(vis[i]);
	rep(i, 1, n) printf("%d ", a[i]); puts("");
	return 0;
}
