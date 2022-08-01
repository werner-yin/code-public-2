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

int n, p[N], dt[N], a[N], b[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) dt[p[i] = in] = i;
	per(i, n, 1) dt[i] -= dt[i - 1];
	dt[1] = 0;
	rep(i, 2, n) {
		if(dt[i] > 0) a[i] = dt[i] + 1, b[i] = -1;
		else a[i] = 1, b[i] = dt[i] - 1;
	}
	rep(i, 1, n) a[i] += a[i - 1], b[i] += b[i - 1];
	rep(i, 1, n) a[i] += 1, b[i] -= b[n] - 1;
	rep(i, 1, n) printf("%d ", a[i]); puts(""); rep(i, 1, n) printf("%d ", b[i]); puts(""); 
	return 0;
}
