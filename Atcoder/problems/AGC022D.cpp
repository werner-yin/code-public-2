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

int n, L, x[N], t[N], top, sum;
bool l[N], r[N], del[N];
ll ans;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, L = in, ans = n + 1; rep(i, 1, n) x[i] = in;
	rep(i, 1, n) t[i] = in, ans += t[i] / (L << 1), t[i] %= L << 1;
	rep(i, 1, n) {
		if(t[i] == 0) { ans--; del[i] = 1; continue; }
		l[i] = 2 * (L - x[i]) >= t[i];
		r[i] = 2 * x[i] >= t[i];
		del[i] = !l[i] && !r[i];
	}
	int p = n;
	rep(i, 1, n - 1) {
		if(del[i]) continue;
		if(!l[i]) { p = i; break; }
		if(r[i]) top++; else if(top) top--, ans--;
	}
	sum += top; top = 0;
	per(i, n - 1, p) {
		if(del[i]) continue;
		if(!r[i]) continue;
		if(l[i]) top++; else if(top) top--, ans--;
	} sum += top;
	ans -= sum >> 1; ans -= l[n]; ans *= L << 1; cout << ans << endl;
	return 0;
}
