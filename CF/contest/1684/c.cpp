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

int n, m, pos1, pos2;
vector < vec > a;

void swp(int x, int y) {
	pos1 = x, pos2 = y;
	rep(i, 1, n) swap(a[i][x], a[i][y]);
}

void solve() {
	n = in, m = in; //cerr << "!" << n << " " << m << endl;
	a = vector < vec > (n + 1, vec(m + 1, 0));
	rep(i, 1, n) rep(j, 1, m) a[i][j] = in;
	int lst = -1;
	rep(j, 1, m - 1) {
		bool must = 0, mustn = 0;
		rep(i, 1, n) if(a[i][j] > a[i][j + 1]) must = true; else if(a[i][j] < a[i][j + 1]) mustn = true;
		if(must && mustn) return puts("-1"), void();
		if(must) {
			if(lst != -1) { swp(lst, j + 1); lst = -114; break; }
			else lst = j;
		}
	}
	if(lst == -1) pos1 = 1, pos2 = 1;
	else if(lst != -114) swp(lst, lst + 1);
	rep(i, 1, n) rep(j, 1, m - 1) if(a[i][j] > a[i][j + 1]) return puts("-1"), void();
	printf("%d %d\n", pos1, pos2);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
