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

const int N = 65;

ll C[N][N];
ll f[N][N * N][N], ans;
int n, K;

void init(int l) {
	rep(i, 0, l) {
		C[i][0] = 1;
		rep(j, 1, i) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
}

int C2(int x) { return x * (x - 1) / 2; }

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; init(n * 2);
	rep(i, 1, n * 2 + 1) if(C2(i) <= K) f[i][C2(i)][i - 1] = 1;
	rep(i, 0, n * 2) rep(j, 0, K) rep(k, 0, n) if(f[i][j][k]) {
		rep(x, k + 2, 2 * n + 1 - i) if(j + C2(x) <= K) {
			f[i + x][j + C2(x)][x - k - 2] += f[i][j][k] * C[x - 1][k + 1];
		} else break;
	}
	ans = f[2 * n + 1][K][0]; //cerr << f[2 * n + 1][K][0] << endl;
	rep(i, 0, n * 2 + 1) rep(j, 0, K) rep(k, 1, n) if(f[i][j][k] && f[2 * n - i + 1][K - j][k - 1])
		ans += f[i][j][k] * f[2 * n - i + 1][K - j][k - 1];
	cout << ans << endl;
	return 0;
}
