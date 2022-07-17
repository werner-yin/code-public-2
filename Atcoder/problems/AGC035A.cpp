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

int n, a[N];
map < int, int > f;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in, f[a[i]]++;
	if(n % 3 != 0 || f.size() == 1) {
		bool fl = 1; rep(i, 1, n) fl &= !a[i];
		cout << (fl ? "Yes" : "No") << endl;
	} else {
		bool fl = f.size() <= 3; int ret = 0;
		for(auto v : f) fl &= v.se == n / 3 || v.se == n / 3 * 2 || v.se == n, ret ^= v.se == n / 3 * 2 ? 0 : v.fi;
		fl &= ret == 0; cout << (fl ? "Yes" : "No") << endl;
	}
	return 0;
}
