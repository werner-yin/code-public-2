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
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in;
	if(n == 1) puts("Unlucky"); else if(n == 2) puts("10"); else if(n == 3) puts("Unlucky"); else if(n == 5) puts("10000");
	else if(n == 7) puts("0101001");
	else {
		bool fl1 = 0, fl2 = 0;
		if(n % 4 == 1 || n % 4 == 3) fl1 = true;
		if(n % 4 == 2 || n % 4 == 3) fl2 = 1;
		while(n >= 4) printf("0110"), n -= 4, (fl1 && (printf("0"), fl1 = 0));
		if(fl2) printf("01"); puts("");
	}
	return 0;
}
