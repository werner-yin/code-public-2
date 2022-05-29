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

int n, a[4][N], b[N], tot;
int rev;
bool re[N];

int tr[N];
void add(int x, int v) { for(; x <= n; x += x & -x) tr[x] += v; }
int query(int x) { int ret = 0; for(; x; x -= x & -x) ret += tr[x]; return ret; }

map < tuple < int, int, int >, int > f;

#define GG return puts("No"), 0;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, 3) rep(j, 1, n) a[i][j] = in;
	rep(i, 1, n) {
		int x = ++tot, y = ++tot, z = ++tot;
		f[{ x, y, z }] = i;
	}
	rep(i, 1, n) {
		int x = a[1][i], y = a[2][i], z = a[3][i];
		if(x > z) rev++, swap(x, z), re[i] = 1;
		if(!f.count({ x, y, z })) GG;
		int id = f[{ x, y, z }];
		b[i] = id;
	}
	rep(i, 1, n) if((b[i] & 1) ^ (i & 1)) GG;
	int tret = 0;
	rep(i, 1, n) if(i & 1) {
		tret ^= (query(n) - query(b[i])) & 1;
		add(b[i], 1);
	} memset(tr, 0, sizeof tr);
	rep(i, 1, n) if(~i & 1) {
		tret ^= (query(n) - query(b[i])) & 1;
		add(b[i], 1);
	} if(tret != (rev & 1)) GG;
	puts("Yes");
	return 0;
}
