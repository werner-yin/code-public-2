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
using vec = vector < ll >;
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
const ll inf = 1e18;

int n, a[N], K;

vec solve(int n, int l, int r) {
	if(n == 1) {
		vec ret(r - l + 1);
		rep(i, l, r) ret[i - l] = i >= 1 && i <= K ? a[i] : inf;
		return ret;
	}
	if(n & 1) {
		int tl = max(0, l - K); vec ret(r - l + 1, inf), tret = solve(n - 1, tl, r);
		rep(j, tl, r) rep(k, 1, K) 
			if(j + k <= r) {
				if(j + k >= l) chkmin(ret[j + k - l], tret[j - tl] + a[k]);
			} else break;
		return ret;
	}
	int tl = max(0, (l - K) / 2), tr = (r + K) / 2;
	vec ret(r - l + 1, inf), tret = solve(n / 2, tl, tr);
	//cerr << "!" << n << " " << l << " "<< r << " : "; for(auto v : tret) cerr << v << " "; cerr << endl;
	rep(i, tl, tr)
		rep(j, tl, tr)
		if(i + j >= l && i + j <= r)
			chkmin(ret[i + j - l], tret[i - tl] + tret[j - tl]);
	return ret;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; rep(i, 1, K) a[i] = in;
	vec ret = solve(n, 2 * n - 2, 2 * n - 2); cout << ret[0] << endl;
	return 0;
}
