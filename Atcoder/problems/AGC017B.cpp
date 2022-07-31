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

ll n, A, B, C, D, vn;

#define GG return puts("NO"), 0;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	vn = n = in - 1; A = in, B = in, C = in, D = in;
	B -= A; B = abs(B); B -= D * n;
	if(B > 0) GG;
	B = abs(B);
	while(B >= 2 * D && n) n--, B -= 2 * D;
	if((B - (D - C) * n) > 0) {
		if(n) {
			B -= 2 * D, n--;
			if(B > 0) GG;
			cerr << B << " " << n << endl;
			B = abs(B);
			if(B - (D - C) * (vn - n) > 0) GG;
		} else GG;
	}
	puts("YES"); 
	return 0;
}
