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

int n, x, l, r, edp;
bool v[N];
int p[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, x = in; l = r = x;
	int cur = (n - 1) / 2, fl = 0; p[1] = x; if(n % 2 == 0 && x == n / 2 + 1) fl = 1;
	vec pot; rep(i, 1, n) if(i != x) pot.eb(i);
	rep(i, 2, n) {
#ifdef YJR_2333_TEST
		cerr << i << " " << l << " " << r << " " << cur << endl;
#endif
		p[i] = pot[cur]; if(fl) cur += i - 1; else cur -= i - 1; fl ^= 1;
	}
	rep(i, 1, n) printf("%d ", p[i]); puts("");
	return 0;
}
