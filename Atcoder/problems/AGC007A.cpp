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

const int N = 20;

int h, w;
char s[N][N];

#define GG return puts("Impossible"), 0;
#define OK return puts("Possible"), 0;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	h = in, w = in; rep(i, 1, h) scanf("%s", s[i] + 1);
	int x = 1, y = 1;
	while(x <= h && y <= w) {
		if(s[x][y] == '.') GG;
		s[x][y] = '.';
		if(x < h && s[x + 1][y] == '#') x++;
		else y++;
	}
	rep(i, 1, h) rep(j, 1, w) if(s[i][j] == '#') GG;
	OK;
	return 0;
}
