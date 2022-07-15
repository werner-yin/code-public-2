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

int n;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; if(__builtin_popcount(n) == 1) return puts("No"), 0;
	puts("Yes");
	int t = n; if(~n & 1) t--;
	rep(i, 2, t) {
		printf("%d %d\n", 1, i);
		printf("%d %d\n", i, i + 1);
		printf("%d %d\n", 1, i + n + 1);
		printf("%d %d\n", i + n, i + n + 1);
		if(i == 2) printf("%d %d\n", n + 1, i + 1);
		i++;
	}
	if(t != n) {
		rep(i, 2, n) if((n ^ i ^ 1) <= n && (n ^ i ^ 1) > 0) {
			int t = n ^ i ^ 1;
			printf("%d %d\n", i, n);
			printf("%d %d\n", t + n, n + n);
			break;
		}
	}
	return 0;
}
