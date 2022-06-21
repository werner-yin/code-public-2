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

const int N = 500 + 10;

int a[N][N];
int H, W, h, w, rev;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	H = in, W = in, h = in, w = in;
	if(H % h == 0 && W % w == 0) return puts("No"), 0;
	if(H % h == 0) swap(H, W), swap(h, w), rev ^= 1;
	rep(i, 1, H) {
		if(i % h == 1) rep(j, 1, W) a[i][j] = H * (h - 1) - 1;
		else rep(j, 1, W) a[i][j] = -H;
	}
	if(rev) swap(H, W);
	puts("Yes");
	rep(i, 1, H) { rep(j, 1, W) printf("%d ", rev ? a[j][i] : a[i][j]); puts(""); }
	return 0;
}
