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

const int N = 510;

int n, L[N][N], R[N][N], s[N][N], w[N][N];
char t[N];
ll ans;

void dfs(int x, int y) {
	if(!w[x][y] || w[x - 1][y] || w[x][y - 1]) return; rep(j, y, n) s[x][j] -= w[x][y]; w[x][y] = 0;
	dfs(x + 1, y), dfs(x, y + 1);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) {
		scanf("%s", t + 1);
		rep(j, 1, n) w[i][j] = t[j] == '#' ? 0 : t[j] - '0', L[i][j] = n + 1, s[i][j] = s[i][j - 1] + w[i][j];
	}
	per(i, n, 1) per(j, n, 1)
		if(w[i][j]) {
			L[j][i] = R[j][i] = j; ll tot = 0;
			rep(k, i, n) {
				if(j < n)
					chkmin(L[j][k], L[j + 1][k]), chkmax(R[j][k], R[j + 1][k]);
				if(L[j][k] <= R[j][k]) tot += s[k][R[j][k]] - s[k][L[j][k] - 1];
			}
			ans += (tot - w[i][j]) * w[i][j]; dfs(i, j);
		} else {
			rep(k, i, n) L[j][k] = n + 1, R[j][k] = 0;
		}
	cout << ans << endl;
	return 0;
}
