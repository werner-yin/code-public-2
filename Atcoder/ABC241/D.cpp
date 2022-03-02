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

multiset < ll > s;
int k, Q; ll x;

ll p(multiset < ll > :: iterator it, int k) {
	rep(i, 1, k) {
		if(it == s.begin()) return -1;
		it--;
	} return *it;
}

ll ss(multiset < ll > :: iterator it, int k) {
	rep(i, 1, k - 1) {
		if(it == s.end()) return -1;
		it++;
	} if(it == s.end()) return -1;
	return *it;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	Q = in;
	while(Q--) {
		int op = in; ll x = lin; int k;
		if(op == 1) s.insert(x);
		else if(op == 2) {
			k = in; auto it = s.upper_bound(x);
			printf("%lld\n", p(it, k));
		} else {
			k = in; auto it = s.lower_bound(x);
			printf("%lld\n", ss(it, k));
		}
	}
	return 0;
}
