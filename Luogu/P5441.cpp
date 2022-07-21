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

ll C3(int x) { return 1ll * x * (x - 1) * (x - 2) / 6; }
int n, a[N];

ll C4(int x) { return 1ll * x * (x - 1) * (x - 2) * (x - 3) / 24; }

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; if(n == 1) { cout << 0 << endl; cout << 0 << endl; return 0; }
	cout << C4(n) - C3(n - 3 >> 1) * n << endl;
	rep(i, 1, n) {
		rep(j, 1, n) a[j] = 0;
		rep(j, 1, n + 1 >> 1) a[(i + j - 1) % n + 1] = 1;
		rep(j, 1, n) printf("%d ", a[j]); puts("");
	}
	return 0;
}
