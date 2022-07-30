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

ll n, a, b;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = lin, a = lin, b = lin;
	if(a <= b) cout << max(0ll, n - a + 1) << endl;
	else {
		/*
		ll ret = 0;
		rep(i, 1, 5000) {
			cerr << max(0ll, (i - a + 1)) / a * b + min(max(0ll, (i - a + 1)) % a, b) << " " << ret << endl;
			if(i >= a && (i - a) % a < b) ret++;
			assert(max(0ll, (i - a + 1)) / a * b + min(max(0ll, (i - a + 1)) % a, b) == ret);
		}
		*/
		cout << max(0ll, (n - a + 1)) / a * b + min(max(0ll, (n - a + 1)) % a, b) << endl;
	}
	return 0;
}
