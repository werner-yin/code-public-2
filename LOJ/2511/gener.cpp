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

const int N = 1e5 + 10;

map < int, bool > f[17][N];
int s, t, peo;
char tpeo[N];

bool canknow(int turn, int x, int y) {
	if(f[turn][x].count(y)) return f[turn][x][y];
	if(turn == 1) {
		int cnt = 0;
		if(peo == 0) {
			rep(i, s, x * y) if(x * y % i == 0 && x * y / i >= i) cnt++;
		}
		else 
			rep(i, s, x + y) if(x + y - i >= i) cnt++;
		return f[turn][x][y] = cnt == 1;
	}
	if(turn > 2 && canknow(turn - 2, x, y)) return f[turn][x][y] = 1;
	int cnt = 0;
	if((turn + peo + 1) % 2 == 0) {
		rep(i, s, x * y) if(x * y % i == 0 && x * y / i >= i) cnt += !canknow(turn - 1, i, x * y / i);
	} else
		rep(i, s, x + y) if(x + y - i >= i) cnt += !canknow(turn - 1, i, x + y - i);
	if(cnt == 1 && !canknow(turn - 1, x, y)) return f[turn][x][y] = 1;
	return f[turn][x][y] = 0;	
}

int qct(int x, int y) {
	rep(i, 1, t + 1) if(canknow(i, x, y)) return i;
	return -1;
}

int main() {
	s = in, scanf("%s", tpeo); peo = tpeo[0] == 'B'; t = in;
	rep(sum, s + s, N - 10)
		rep(x, 1, sum - 1) {
		int y = sum - x;
		if(qct(x, y) == t + 1) {
			if((t + peo + 1) % 2 == 0) {
				int cnt = 0;
				rep(i, s, x * y) if(x * y % i == 0 && x * y / i >= i) cnt += qct(i, x * y / i) == (t + 1);
				if(cnt == 1) return printf("%d %d\n", x, y), 0;
			} else {
				int cnt = 0;
				rep(i, s, x + y) if(x + y - i >= i) cnt += qct(i, x + y - i) == (t + 1);
				if(cnt == 1) return printf("%d %d\n", x, y), 0;
			}
		}
	}
	return 0;
}
