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

const int N = 2e6 + 10;

int n, K;
char s[N];
int f[21][1 << 20], nxt[21][1 << 20], ans, tb = -1, ret[1 << 20];

char get() {
	char ch = getchar(); while(!isdigit(ch)) ch = getchar();
	return ch;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in;
	rep(i, 0, n) {
		rep(j, 0, (1 << i) - 1) 
			f[i][j] = get() - '0';
	}
	rep(i, 1, n) {
		rep(j, 0, (1 << i) - 1) {
			int v = j >> i - 1 & 1; nxt[i][j] = -1;
			per(k, i - 2, 0) if((j >> k & 1) ^ v) { nxt[i][j] = k + 1; break; }
		}
	}
	rep(lena, 0, n) {
		rep(j, 0, (1 << lena) - 1) ret[j] = 0;
		rep(lenb, 0, n - lena)
			rep(j, 0, (1 << lena + lenb) - 1)
			ret[j >> lenb] += f[lena + lenb][j];
		rep(j, 0, (1 << lena) - 1) if(ret[j] >= K) { ans = j; tb = lena - 1; break; }
		rep(lenb, 0, n - lena)
			rep(j, 0, (1 << lena + lenb) - 1) if(f[lena + lenb][j]) {
			int A = j >> lenb, B = j ^ A << lenb, p = nxt[lenb][B];
			if(p != -1) f[lena + p][(A << p) | (B & ((1 << p) - 1))] += f[lena + lenb][j];
		}
	}
	per(i, tb, 0) putchar((ans >> i & 1) + '0'); puts("");
	return 0;
}
