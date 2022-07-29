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

int n, m, a, b, ta, tb;
char s[1010][1010];
bool fl;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, a = in, b = in;
	if(n & 1) swap(n, m), swap(a, b), fl = 1;
	if(a < b && n & 1 && m & 1) swap(n, m), swap(a, b), fl ^= 1;
	rep(i, 1, n) rep(j, 1, m) s[i][j] = '.';
	if(~n & 1) {
		rep(i, 1, n) {
			rep(j, 1, m) {
				if(s[i][j] == '.' && s[i][j + 1] == '.' && a) a--, s[i][j] = '<', s[i][j + 1] = '>';
				if(s[i + 1][j] == '.' && s[i + 1][j + 1] == '.' && a) a--, s[i + 1][j] = '<', s[i + 1][j + 1] = '>';
			}
			i++;
		}
		rep(i, 1, n) rep(j, 1, m)
			if(s[i][j] == '.' && s[i + 1][j] == '.' && b)
				s[i][j] = '^', s[i + 1][j] = 'v', b--;
		if(a || b) return puts("NO"), 0;
	} else {
		bool tl = 0; ta = a, tb = b;
		rep(i, 1, 1)
			rep(j, 1, m) 
			if(s[i][j] == '.' && s[i][j + 1] == '.' && a) a--, s[i][j] = '<', s[i][j + 1] = '>';
		rep(i, 2, n) {
			rep(j, 1, m) {
				if(s[i][j] == '.' && s[i][j + 1] == '.' && a) a--, s[i][j] = '<', s[i][j + 1] = '>';
				if(!a) { tl = 1; }
				if(s[i + 1][j] == '.' && s[i + 1][j + 1] == '.' && a) a--, s[i + 1][j] = '<', s[i + 1][j + 1] = '>';
				if(!a) break;
			} if(!a) break;
			i++;
		}
		rep(i, 1, n) rep(j, 1, m)
			if(s[i][j] == '.' && s[i + 1][j] == '.' && b)
				s[i][j] = '^', s[i + 1][j] = 'v', b--;
		if(a || b) {
			a = ta, b = tb;
			rep(i, 1, n) rep(j, 1, m) s[i][j] = '.';
			rep(i, 1, 1)
				rep(j, 1, m) 
				if(s[i][j] == '.' && s[i][j + 1] == '.' && a) a--, s[i][j] = '<', s[i][j + 1] = '>';
			s[1][m] = s[2][m] = 'b';
			rep(i, 2, n) {
				rep(j, 2, m) {
					if(s[i][j] == '.' && s[i][j + 1] == '.' && a) a--, s[i][j] = '<', s[i][j + 1] = '>';
					if(s[i + 1][j] == '.' && s[i + 1][j + 1] == '.' && a) a--, s[i + 1][j] = '<', s[i + 1][j + 1] = '>';
					if(!a) break;
				} if(!a) break; i++;
			}
			s[1][m] = s[2][m] = '.';
			rep(i, 1, n) rep(j, 1, m)
				if(s[i][j] == '.' && s[i + 1][j] == '.' && b)
					s[i][j] = '^', s[i + 1][j] = 'v', b--;
		}
		if(a || b) return puts("NO"), 0;
	}
	//rep(i, 1, n) { rep(j, 1, m) cerr << s[i][j]; cerr << endl; }
	if(fl) swap(n, m);
	auto trans = [&](char ch) {
		if(ch == '.') return ch;
		if(ch == '<' || ch == '^') return char(ch ^ '<' ^ '^');
		else return char(ch ^ '>' ^ 'v');
	}; puts("YES");
	rep(i, 1, n) rep(j, 1, m) {
		if(fl) putchar(trans(s[j][i]));
		else putchar(s[i][j]); if(j == m) puts("");
	}
	return 0;
}
