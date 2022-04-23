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

ll tot0, tot1;
int a, b, c, d, e, f, x;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	a = in, b = in, c = in, d = in, e = in, f = in, x = in;
	swap(b, a);swap(d, e);
	rep(i, 0, x - 1) {
		if(i % (b + c) < b) tot0 += a;
		if(i % (e + f) < e) tot1 += d, cerr << i << " ";
	} cerr << tot0 << " " << tot1 << endl;
	if(tot0 == tot1) puts("Draw");
	else if(tot0 > tot1) puts("Takahashi");
	else puts("Aoki");
	return 0;
}
