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

const int N = 5010;

int n, a[N];
ll f[N], A, B;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, A = in, B = in; rep(i, 1, n) a[i] = in;
	a[n + 1] = n + 1;
	rep(i, 1, n + 1) {
		f[i] = 1e18; ll ret = 0;
		per(j, i - 1, 0) {
			if(a[j] < a[i]) chkmin(f[i], f[j] + ret);
			if(a[j] > a[i]) ret += A; else ret += B;
		} 
	} cout << f[n + 1] << endl;
	return 0;
}
