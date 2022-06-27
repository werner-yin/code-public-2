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

int n, x, y, a[N], b[N], c[N], mx;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, x = in, y = in;
	rep(i, 1, n) a[i] = b[i] = in, a[i] %= (x + y);
	if(x <= y) {
		rep(i, 1, n) if(a[i] >= x) return puts("First"), 0;
		puts("Second");
	} else {
		bool fl = 0;
		rep(i, 1, n)
			if(b[i] >= x && (b[i] - x) % (x + y) < y) fl = 1;
			else if(a[i] >= y) return puts("Second"), 0;
		puts(fl ? "First" : "Second");
	}
	return 0;
}
