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

int h, w, n, sr, sc;
char s[N], t[N];

bool solve0(int x, int lim, char a, int pw, char b) {
	//cerr << x << " " << lim << " " << a << " " << pw << " " << b << endl;
	rep(i, 1, n) {
		if(s[i] == a) x += pw;
		chkmin(x, lim);
		if(x <= 0) return 1;
		if(t[i] == b) x -= pw;
		chkmin(x, lim);
		if(x <= 0) return 1;
	} //cerr << "!" << x << endl;
	return 0;
}

bool solve1(int x, int lim, char a, int pw, char b) {
	//cerr << x << " " << lim << " " << a << " " << pw << " " << b << endl;
	rep(i, 1, n) {
		if(s[i] == a) x += pw;
		if(x > lim) return 1;
		chkmax(x, 1);
		if(t[i] == b) x -= pw;
		if(x > lim) return 1;
		chkmax(x, 1);
	} //cerr << "!" << x << endl;
	return 0;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	h = in, w = in, n = in; sr = in, sc = in; scanf("%s", s + 1); scanf("%s", t + 1);
	bool ans = solve0(sc, w, 'L', -1, 'R') || solve1(sc, w, 'R', 1, 'L') || solve0(sr, h, 'U', -1, 'D') || solve1(sr, h, 'D', 1, 'U');
	if(ans) puts("NO"); else puts("YES");
	return 0;
}
