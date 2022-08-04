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

const int N = 2010;

char s[N][N];
int n, fa[N];

void solve() {
	n = in;
	rep(i, 1, n) scanf("%s", s[i] + i);
	rep(i, 1, n) fa[i] = i;
	rep(j, 1, n) per(i, j - 1, 1) if(s[i][j] == '1') {
		if(fa[j] <= i) continue;
		cout << i << " " << j << endl;
		if(fa[fa[j] - 1] > i) {
			cout << fa[j] - 1 << " " << i << endl;
			per(t, fa[fa[j] - 1] - 1, i + 1) if(fa[t] == t)
				cout << j << " " << t << endl;
		} rep(t, i, j) chkmin(fa[t], fa[i]);
	}
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
