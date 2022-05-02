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

int n, a[N], ans = 1e9;

int solve(int A, int B) {
	if(A < B) swap(A, B);
	int pt = min(A - B, (A + 1) / 2), ret = pt;
	A -= pt * 2; B -= pt; if(A <= 0 && B <= 0) return ret;
	pt = max(A, B) / 3; ret += pt * 2;
	A -= pt * 3, B -= pt * 3;
	//ret += (A > 0) + (B > 0);
	if(A || B) ret += 1 + (A == 2 && B == 2);
	return ret;
}

int tsolve(int A, int B) {
	if(A < B) swap(A, B);
	int ret = min(A, B); A -= ret; B -= ret;
	ret += (A + 1) / 2; return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in;
	rep(i, 1, n) {
		int ret = 1e9;
		if(i > 1) chkmin(ret, solve(a[i], a[i - 1]));
		if(i < n) chkmin(ret, solve(a[i], a[i + 1]));
		chkmin(ans, ret);
	}
	rep(i, 2, n - 1) chkmin(ans, tsolve(a[i + 1], a[i - 1]));
	sort(a + 1, a + n + 1);
	chkmin(ans, (a[1] + 1) / 2 + (a[2] + 1) / 2); cout << ans << endl;
	return 0;
}
