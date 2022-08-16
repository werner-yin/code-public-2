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
int a[510][510];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	int K = in;
	if(K <= 500) {
		n = K;
		printf("%d\n", n);
		rep(i, 1, n) {
			rep(j, 1, n) printf("%d ", i);
			puts("");
		}
	} else {
		n = 500;
		rep(i, 1, n) rep(j, 1, n) a[i][j] = (i + j - 2) % 500 + 1;
		rep(i, 501, K) {
			rep(j, 1, n) {
				assert(a[(i - j) % 500 + 1][j] == i - 500);
				a[(i - j) % 500 + 1][j] = i;
				j++;
			}
		}
		printf("%d\n", n);
		rep(i, 1, n) rep(j, 1, n) printf("%d%c", a[i][j], " \n"[j == n]);
	}
	return 0;
}
