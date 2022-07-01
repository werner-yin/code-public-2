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

int n, l, t;
int a[N], x[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, l = in, t = in;
	int shift = 0;
	rep(i, 0, n - 1) {
		a[i] = in, x[i] = in;
		int npos = a[i] + (x[i] == 1 ? t : -t);
		shift += (int)floor(1. * npos / l) % n; shift %= n; shift += n; shift %= n; a[i] = (npos % l + l) % l;
	} sort(a, a + n);
	rep(i, 0, n - 1) printf("%d\n", a[(i + shift) % n]);
	return 0;
}
