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

int n, K, mat[N];

void solve() {
	n = in; K = in;
	if(K == n - 1) {
		if(n == 4) puts("-1");
		else {
			rep(i, 0, n - 1) mat[i] = n - i - 1;
			mat[n - 1] = n - 2; mat[n - 2] = n - 1;
			mat[1] = 3; mat[3] = 1; mat[0] = n - 4;
			rep(i, 0, n - 1) if(mat[i] > i) printf("%d %d\n", i, mat[i]);
		}
	}
	else if(K == 0) {
		rep(i, 0, n - 1) mat[i] = n - i - 1;
		rep(i, 0, n - 1) if(mat[i] > i) printf("%d %d\n", i, mat[i]);
	} else {
		rep(i, 0, n - 1) mat[i] = n - i - 1;
		mat[K] = n - 1; mat[n - 1] = K;
		mat[0] = n - K - 1; mat[n - K - 1] = 0;
		rep(i, 0, n - 1) if(mat[i] > i) printf("%d %d\n", i, mat[i]);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
