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

int n;
bool fl;
ll a[N], L, R, s[2][N];

ll S(int l, int r, int p) { return s[p][r] - s[p][l - 1]; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, L = lin, R = lin; rep(i, 1, n) a[i] = in; sort(a + 1, a + n + 1);
	rep(i, 1, n) s[0][i] = s[0][i - 1], s[1][i] = s[1][i - 1], s[i & 1][i] += a[i];
	rep(i, 1, n) rep(j, i + 1, n) {
		fl |= S(1, i - 1, 1) + a[i] + S(i + 1, j - 1, 0) + S(j + 1, n, 1) >= L && S(1, i - 1, 0) + a[i] + S(i + 1, j - 1, 1) + S(j + 1, n, 0) <= R;
		fl |= S(1, i - 1, 1) + S(i + 1, j - 1, 0) + a[j] + S(j + 1, n, 1) >= L && S(1, i - 1, 0) + S(i + 1, j - 1, 1) + a[j] + S(j + 1, n, 0) <= R;
	} puts(fl ? "Alice" : "Bob");
	return 0;
}
