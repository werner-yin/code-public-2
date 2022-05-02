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

int ask(int x) { cout << "? " << x << endl; cin >> x; return x; }

int main() {
	cin >> n;
	int l = n, r = n * 2000;
	while(l <= r) {
		int mid = l + r >> 1;
		if(ask(mid) != 1) l = mid + 1;
		else r = mid - 1;
	}
	int len = l, ans = len;
	rep(i, 2, n) {
		int p = -1;
		per(j, len, len - i + 1) if(j % i == 0) p = j;
		int t = ask(p / i);
		if(t != 0) chkmin(ans, t * (p / i));
	} cout << "! " << ans << endl;	
	return 0;
}
