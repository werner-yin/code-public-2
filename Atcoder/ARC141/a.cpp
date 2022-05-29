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

ll n;

int len, a[N], b[N], op[N];
int v[N];

ll calc(int l) {
	bool fl = 0;
	rep(i, 1, len) v[i] = 0;
	rep(i, 1, l) {
		b[i] = a[i];
		for(int j = i; j <= len; j += l) {
			if(a[j] < b[i]) v[j] = 1;
			else if(a[j] > b[i]) v[j] = -1;
			op[j] = i;
		}
	}
	int pos = -1;
	rep(i, 1, len)
		if(v[i] == 1) { pos = i; break; }
		else if(v[i] == -1) break;
	if(pos != -1) {
		//cerr << "!" << pos % l + 1 << endl;
		per(i, l, 1) if(b[i]) { b[i]--; rep(j, i + 1, l) b[j] = 9; break; }
	}
	rep(i, l + 1, len)
		b[i] = b[i - l];
	ll ret = 0;
	rep(i, 1, len) ret = ret * 10 + b[i];
	//cerr << l << " " << ret << endl;
	return ret;
}

void solve() {
	n = lin; len = 0;
	while(n) a[++len] = n % 10, n /= 10;
	reverse(a + 1, a + len + 1);
	ll ans = 0; rep(i, 1, len - 1) ans = ans * 10 + 9;
	rep(i, 1, len - 1) if(len % i == 0) chkmax(ans, calc(i));
	cout << ans << endl;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
