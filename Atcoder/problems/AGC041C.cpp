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

const int N = 1010;
const pii H[4] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

char s[N][N];
int n;

string getaround(int x, int y) {
	string pot = "";
	rep(i, 0, 3) {
		int nx = x + H[i].fi, ny = y + H[i].se;
		if(s[nx][ny]) pot += s[nx][ny];
	} return pot;
}

void putlin(int x, int y) {
	assert(x <= n && y <= n - 1);
	assert(!s[x][y] && !s[x][y + 1]);
	string pot = getaround(x, y) + getaround(x, y + 1);
	rep(i, 'a', 'z') if(pot.find(i) == -1) return s[x][y] = s[x][y + 1] = i, void();
}

void putrow(int x, int y) {
	//	cerr << x << " ! " << y << endl;
	assert(x <= n - 1 && y <= n);
	assert(!s[x][y] && !s[x + 1][y]);
	string pot = getaround(x, y) + getaround(x + 1, y);
	rep(i, 'a', 'z') if(pot.find(i) == -1) return s[x][y] = s[x + 1][y] = i, void();
}

void put6x6(int x, int y) {
	x--, y--;
	putlin(x + 1, y + 1); putlin(x + 2, y + 1); putlin(x + 3, y + 1);
	putrow(x + 1, y + 3); putrow(x + 1, y + 4);
	putrow(x + 3, y + 3); putrow(x + 3, y + 4);
	putrow(x + 5, y + 3); putrow(x + 5, y + 4);
	putlin(x + 4, y + 5); putlin(x + 5, y + 5); putlin(x + 6, y + 5);
}

void put7x7(int x, int y) {
	x--, y--;
	putlin(x + 3, y + 1); putlin(x + 4, y + 1); putlin(x + 5, y + 1);
	putrow(x + 1, y + 3); putrow(x + 1, y + 4); putrow(x + 1, y + 5);
	putlin(x + 3, y + 6); putlin(x + 4, y + 6); putlin(x + 5, y + 6);
	putrow(x + 6, y + 3); putrow(x + 6, y + 4); putrow(x + 6, y + 5);
	putlin(x + 3, y + 3); putrow(x + 4, y + 5);
}

void put3x3(int x, int y) { // 2
	//cerr << x << " " << y << endl;
	x--, y--;
	putlin(x + 1, y + 1); putrow(x + 1, y + 3);
	putlin(x + 3, y + 2); putrow(x + 2, y + 1);
}

void put4x4(int x, int y) {
	x--, y--; //cerr << x << " " << y << endl;
	putrow(x + 1, y + 1); putrow(x + 1, y + 2);
	putlin(x + 1, y + 3); putlin(x + 2, y + 3);
	putlin(x + 3, y + 1); putlin(x + 4, y + 1);
	putrow(x + 3, y + 3); putrow(x + 3, y + 4);
}

void put8x8(int x, int y) {
	put4x4(x, y); put4x4(x + 4, y + 4);
}

void put5x5(int x, int y) {
	x--, y--;
	putlin(x + 1, y + 1); putlin(x + 1, y + 3); putrow(x + 1, y + 5);
	putrow(x + 2, y + 1); putlin(x + 2, y + 2); putrow(x + 3, y + 4);
	putrow(x + 3, y + 5); putrow(x + 4, y + 1); putlin(x + 5, y + 2);
	putlin(x + 5, y + 4);
}

int main() {
#ifndef ONLINE_JUDGE
	//freopen("1.in", "r", stdin);
#endif
	n = in;
	if(n <= 2) puts("-1");
	else {
		if(n % 3 == 0) {
			for(int x = 1; x < n; x += 3) 
				put3x3(x, x);
		} else if(n % 6 == 1) {
			for(int x = 1; x <= n - 7; x += 6) {
				put6x6(x, x);
			} put7x7(n - 6, n - 6);
		} else if(n % 6 == 5) {
			for(int x = 1; x <= n - 5; x += 6) {
				put6x6(x, x);
			} put5x5(n - 4, n - 4);
		} else if(n % 6 == 4) {
			for(int x = 1; x <= n - 4; x += 6) {
				put6x6(x, x);
			} put4x4(n - 3, n - 3);
		} else {
			assert(n % 6 == 2);
			for(int x = 1; x <= n - 8; x += 6) {
				put6x6(x, x);
			} put4x4(n - 3, n - 3); put4x4(n - 7, n - 7);
		}
		rep(i, 1, n) {
			rep(j, 1, n) putchar(s[i][j] ? s[i][j] : '.');
			puts("");
		}
	}
	return 0;
}
