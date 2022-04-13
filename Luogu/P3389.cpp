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

const int N = 110;
const db eps = 1e-6;

db a[N][N];
int n;

void guass() {
	rep(i, 1, n) {
		int p = i; rep(j, i + 1, n) if(fabs(a[j][i]) > fabs(a[p][i])) p = j;
		if(p ^ i) swap(a[i], a[p]); if(fabs(a[i][i]) < eps) return puts("No Solution"), exit(0), void();
		db t = a[i][i]; rep(j, i, n + 1) a[i][j] /= t;
		rep(j, 1, n) if(j ^ i) {
			db t = a[j][i]; if(fabs(t) < eps) continue;
			rep(k, i, n + 1) a[j][k] = a[j][k] - a[i][k] * t;
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) rep(j, 1, n + 1) scanf("%lf", &a[i][j]);
	guass(); rep(i, 1, n) printf("%.2lf\n", a[i][n + 1]);
	return 0;
}
