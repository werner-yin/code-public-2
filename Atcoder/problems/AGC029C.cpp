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

int n, a[N], l, r;

bool check(int mid) {
	map < int, int > f; int len = 0;
	rep(i, 1, n) {
		if(len < a[i]) { len = a[i]; }
		else {
			int pos = a[i];
			while(true) {
				if(pos == 0) return false;
				if(f.count(pos) && f[pos] == mid) {
					pos--; continue;
				} else if(f.count(pos)) {
					f[pos]++; for(int j = pos + 1; j <= a[i]; j++) f.erase(j);
					break;
				} else {
					f[pos] = 2; for(int j = pos + 1; j <= a[i]; j++) f.erase(j);
					break;
				}
			} len = a[i];
			for(auto it = f.lower_bound(len + 1); it != f.end(); ) f.erase(it++);
		}
	} return true;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in;
	bool fl = 1; rep(i, 2, n) fl &= a[i - 1] < a[i];
	if(fl) return puts("1"), 0;
	l = 2, r = n;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(mid)) r = mid - 1;
		else l = mid + 1;
	} cout << l << endl;
	return 0;
}
